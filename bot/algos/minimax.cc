#include "../engine/State.h"
#include "minimax.h"
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

enum OVERRIDE_STATUS {
  DEFAULT = -2,
  EMPTY,
  MYSELF,
  ENEMY1,
  ENEMY2,
  ENEMY3,
  ENEMY4,
  ENEMY5,
  ENEMY6,
  ENEMY7,
  ENEMY8,
  ENEMY9,
  ENEMY10
};

OVERRIDE_STATUS D = DEFAULT;

struct TemporalState {
  unordered_map<Location, OVERRIDE_STATUS> state;

  const OVERRIDE_STATUS & operator[](const Location & l) const {
    auto it = state.find(l);
    if (it == state.end()) {
      return D;
    } else {
      return it->second;
    }
  }
};

int evalState(const TemporalState & local, const vector<Location> & myAnts, const vector<Location> & enemyAnts) {
  State & global = State::getSingleton();
  
  unordered_map<Location, vector<Location>> neighs;
  unordered_map<Location, int> enemies;

  int score = 0;

  auto it1 = local.state.begin();
  for (; it1 != local.state.end(); it1++) {
    auto it2 = it1;
    if (it1->second != DEFAULT && it1->second != EMPTY) {
      for (; it2 != local.state.end(); it2++) {
        if (it2->second != DEFAULT && 
          it2->second != EMPTY && 
          it1->second != it2->second) {
          if (global.distance(it1->first, it2->first) <= global.attackradius) {
            auto & v  = neighs[it1->first];
            auto & v2 = neighs[it2->first];
            v.push_back(it2->first);
            v2.push_back(it1->first);
            enemies[it1->first]++;
            enemies[it2->first]++;
          }
        }
      }
    }
  }

  for (auto & attack: neighs) {
    bool dies = false;
    for (auto & enemy: attack.second) {
      if (enemies[enemy] <= enemies[attack.first]) {
        dies = true;
      } 
    }
    if (dies && local[attack.first] == MYSELF) {
      score -= 1;
    } else if (dies) {
      score += 1;
    }
  }
  return score;
}

int recursiveMinimax(const vector<Location> & myAnts, 
  const vector<Location> & enemyAnts, 
  const unordered_set<Location> & ignore, 
  vector<Decision> & subBest, 
  TemporalState & local,
  bool max) {
  State & global = State::getSingleton();
    
  static vector<Decision> myDecision;
  static vector<Decision> enemyDecision;

  vector<Decision> & actual = (max ? myDecision : enemyDecision);
 
  int it = actual.size();
  Location actualAnt;

  if (max) {
    actualAnt = myAnts[it];
  } else {
    actualAnt = enemyAnts[it];
  }

  if (max && it == myAnts.size()) {
    int score = recursiveMinimax(myAnts, enemyAnts, ignore, subBest, local, false);
    return score;
  }
  if (!max && it == enemyAnts.size()) {
    subBest = myDecision;
    return evalState(local, myAnts, enemyAnts);
  }

  int bestValue;

  local.state[actualAnt] = (OVERRIDE_STATUS)global.getGrid(actualAnt).ant;
  actual.push_back(Decision{
    actualAnt, IMPOSSIBLE
  });
  bestValue = recursiveMinimax(myAnts, enemyAnts, ignore, subBest, local, max);
  actual.pop_back();

  for (FWDirection dir: FDIRECTIONS) {
    Location nl(actualAnt, dir);
    nl.wrap();
    auto au = global.getGrid(nl);
    auto shouldIgnore = ignore.count(nl) > 0;
    if (!au.isWater && 
      ((shouldIgnore || au.ant == -1) &&
       (local[nl] <= EMPTY))) {

      // Cambiar estado
      auto oldStateNl = local[nl];
      auto oldStateAct = local[actualAnt];
      
      local.state[nl] = (OVERRIDE_STATUS)global.getGrid(actualAnt).ant;
      local.state[actualAnt] = EMPTY;
      
      // Cambiar lista de decisiones
      actual.push_back(Decision{
        actualAnt, dir
      });
      vector<Decision> dec;
      int value = recursiveMinimax(myAnts, enemyAnts, ignore, dec, local, max);
      if ((max && value > bestValue) || (!max && value < bestValue)) {
        subBest = dec;
        bestValue = value;
      }
      // Deshacer lista de decisiones
      actual.pop_back();

      // Recuperar estado
      local.state[nl] = oldStateNl;
      local.state[actualAnt] = oldStateAct;
    }
  }
  return bestValue;
}

vector<Decision> minimax(const vector<Location> & myAnts, const vector<Location> & enemyAnts) {
  TemporalState temp;
  vector<Decision> best;

  unordered_set<Location> collisionIgnore;

  // Marcar como libres todas las casillas con hormigas dentro del minimax:
  for (const Location & l: myAnts) {
    collisionIgnore.insert(l);
  }

  for (const Location & l: enemyAnts) {
    collisionIgnore.insert(l);    
  }

  int score = recursiveMinimax(myAnts,enemyAnts, collisionIgnore, best, temp, true);

  return best;
}