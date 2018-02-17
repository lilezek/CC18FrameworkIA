#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>
#include <unordered_set>
#include "Location.h"

/*
    struct for representing a square in the grid.
*/
struct Square
{
  bool isVisible, isWater, isHill, isFood, alreadyMoved;
  int ant, hillPlayer;
  int theAnt;
  std::vector<int> deadAnts;
  std::unordered_set<Location> ownPresence;
  std::unordered_set<Location> enemyPresence;
  int danger;
  double influence;

  Square()
  {
    isVisible = isWater = isHill = isFood = 0;
    ant = hillPlayer = -1;
    theAnt = -1;
    influence = danger = 0;
    alreadyMoved = false;
  };

  /**
   * Devuelve verdadero si se puede andar: no hay otra hormiga ni hay agua.
   */
  bool isWalkable() const
  {
    return !isWater && ant == -1;
  }

  //resets the information for the square except water information
  void reset()
  {
    isVisible = 0;
    isHill = 0;
    isFood = 0;
    ant = hillPlayer = -1;
    theAnt = -1;
    deadAnts.clear();
    ownPresence.clear();
    enemyPresence.clear();
    influence = danger = 0;
    alreadyMoved = false;
  };
};

#endif //SQUARE_H_
