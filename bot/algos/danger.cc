#include "danger.h"
#include <queue>
#include <unordered_set>
#include "../debug.h"
#include "Antgroup.h"
#include "bfs.h"

#define HARDCODED_AGGRO_DISTANCE 17

using namespace std;

void calculateDanger()
{
    State &s = State::getSingleton();
    for (const Location &ant : s.enemyAnts)
    {
        BreadFirstExpansion(ant,
                            [&s, &ant](const Location &l, int distance) {
                                Square &sq = s.getGrid(l);
                                int dist = s.distance(ant, l);
                                if (sq.isWater || dist > HARDCODED_AGGRO_DISTANCE)
                                {
                                    return OBSTACLE;
                                }
                                else
                                {
                                    sq.danger += 1;
                                    sq.enemyPresence.insert(ant);
                                    return CONTINUE;
                                }
                            });
    }

    for (const Location &ant : s.myAnts)
    {
        BreadFirstExpansion(ant,
                            [&s, &ant](const Location &l, int distance) {
                                Square &sq = s.getGrid(l);
                                int dist = s.distance(ant, l);                                
                                if (sq.isWater || dist > HARDCODED_AGGRO_DISTANCE)
                                {
                                    return OBSTACLE;
                                }
                                else
                                {
                                    sq.danger -= 1;
                                    sq.ownPresence.insert(ant);
                                    return CONTINUE;
                                }
                            });
    }
}