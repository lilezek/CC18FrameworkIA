#include "space.h"
#include "../engine/State.h"

const int DIAGONALS[4][2] = { {-1, 1}, {1, 1}, {1, -1}, {-1, -1} };


void calculateSpace(const Location & water) {
  State & state = State::getSingleton();
  
  for (auto & dir: FDIRECTIONS) {
    Location nl(water, dir);
    nl.wrap();
    auto & sq = state.getGrid(nl);
    sq.space--;
  }

  for (auto & dir: DIAGONALS) {
    Location nl(dir);
    nl = nl + water;
    nl.wrap();
    auto & sq = state.getGrid(nl);
    sq.space--;
  }
}