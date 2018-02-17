#include "Antgroup.h"
#include "../engine/State.h"
#include <algorithm>

using namespace std;

AntGroup::AntGroup() : unordered_set(), strength(0) {

}

AntGroup AntGroup::getGroupBattleAt(const Location & at, int limit) {
    State & s = State::getSingleton();
    AntGroup result;

    queue<Location> antsToCheck;
    Square & sqAt = s.getGrid(at);
    antsToCheck.push(at);
    result.insert(at);
    if (sqAt.ant == 0) {
        result.strength++;
    } else if (sqAt.ant > 0) {
        result.strength--;
    }

    while (antsToCheck.size()) {
        const Location & l = antsToCheck.front(); antsToCheck.pop();
        Square & sq = s.getGrid(l);
        if (sq.ant == 0) {
            for (const Location & lEnemyAnt: sq.enemyPresence) {
                if (!result.count(lEnemyAnt)) {
                    result.strength--;
                    result.insert(lEnemyAnt);
                    antsToCheck.push(lEnemyAnt);                    
                }
            }
        } else if (sq.ant > 0) {
            for (const Location & lant: sq.ownPresence) {
                if (!result.count(lant)) {
                    // No insertar hormigas que ya se hayan movido 
                    Square & sqlant = s.getGrid(lant);
                    if (!sqlant.alreadyMoved) {
                        result.strength++;
                        result.insert(lant);
                    }
                    antsToCheck.push(lant);
                }
            }
        }
    }

    if (result.size() > limit) {
        // Ordenar por distancia al punto
        vector<pair<int, Location>> filter;
        for (const Location & l: result) {
            filter.push_back(make_pair(s.distance(l, at), l));
        }
        sort(filter.begin(), filter.end());
        result.clear();
        for (const auto & p: filter) {
            result.insert(p.second);
            if (result.size() >= limit) {
                return result;
            }
        }
    }

    return result;
}

vector<Location> AntGroup::getOwnAnts() {
  vector<Location> result;
  State & s = State::getSingleton();
  for (const Location & l : *this) {
    if (s.getGrid(l).ant == 0) {
      result.push_back(l);
    }
  }
  return result;
}

vector<Location> AntGroup::getEnemyAnts() {
  vector<Location> result;
  State & s = State::getSingleton();
  for (const Location & l : *this) {
    if (s.getGrid(l).ant > 0) {
      result.push_back(l);
    }
  }
  return result;
}