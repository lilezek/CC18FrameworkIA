#ifndef ANTGROUP_H
#define ANTGROUP_H

#include <unordered_set>
#include <vector>
#include "../engine/Location.h"

class AntGroup: public std::unordered_set<Location> {

  public:
    AntGroup();

    std::vector<Location> getOwnAnts();
    std::vector<Location> getEnemyAnts();

    static AntGroup getGroupBattleAt(const Location & at, int limit = 8);

    int strength;
};

#endif