#ifndef MINIMAX_H
#define MINIMAX_H

#include <vector>
#include "../engine/Location.h"

struct Decision {
  Location ant;
  FWDirection to;
};

std::vector<Decision> minimax(const std::vector<Location> & myAnts, const std::vector<Location> & enemyAnts);

#endif