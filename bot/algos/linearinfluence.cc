#include "linearinfluence.h"
#include "../engine/State.h"
#include "bfs.h"

#define HELP_RADIUS 30

void enemyAntInfluence(const Location &ant)
{
    State &s = State::getSingleton();

    // ¿Está cerca de una colina aliada?
    int nearBonus = 0;
    for (const Location &hill : s.myHills)
    {
        if (s.distance(hill, ant) <= s.viewradius)
        {
            nearBonus = 20;
        }
    }

    BreadFirstExpansion(ant,
                        [&s, &ant, nearBonus](const Location &l, int distance) {
                            Square &sq = s.getGrid(l);
                            if (sq.isWater || distance >= HELP_RADIUS)
                            {
                                return OBSTACLE;
                            }
                            else
                            {
                                sq.influence += HELP_RADIUS - distance + nearBonus;
                                return CONTINUE;
                            }
                        });
}

void friendlyAntInfluence(const Location &ant)
{
    State &s = State::getSingleton();
    Square &sq = s.getGrid(ant);

    int danger = sq.danger;

    BreadFirstExpansion(ant,
                        [&s, &ant, danger](const Location &l, int distance) {
                            Square &sq = s.getGrid(l);
                            if (sq.isWater || distance >= HELP_RADIUS)
                            {
                                return OBSTACLE;
                            }
                            else
                            {
                                if (danger > 0)
                                {
                                    sq.influence += danger * 5;
                                }
                                sq.influence += (distance - HELP_RADIUS);
                                return CONTINUE;
                            }
                        });
}

void friendlyHillInfluence(const Location &hill)
{
    // No hacer nada
}

void enemyHillInfluence(const Location &hill)
{
    State &s = State::getSingleton();

    int nearBonus = 50;
    Square &sq = s.getGrid(hill);
    sq.influence += 100;

    BreadFirstExpansion(hill,
                        [&s, &hill, nearBonus](const Location &l, int distance) {
                            Square &sq = s.getGrid(l);
                            int dist = s.distance(l, hill);
                            if (sq.isWater || distance >= HELP_RADIUS)
                            {
                                return OBSTACLE;
                            }
                            else
                            {
                                sq.influence += HELP_RADIUS - distance + nearBonus;
                                return CONTINUE;
                            }
                        });
}

void antInfluence(const Location &ant)
{
    State &s = State::getSingleton();
    auto &sq = s.getGrid(ant);
    getDebugger() << ant << " " << sq.ant << std::endl;
    if (sq.ant == 0)
    {
        friendlyAntInfluence(ant);
    }
    else if (sq.ant > 0)
    {
        enemyAntInfluence(ant);
    }
}

void hillInfluence(const Location &hill)
{
    State &s = State::getSingleton();
    auto &sq = s.getGrid(hill);
    if (sq.hillPlayer == 0)
    {
        friendlyHillInfluence(hill);
    }
    else if (sq.hillPlayer > 0)
    {
        enemyHillInfluence(hill);
    }
}

void foodInfluence(const Location &food)
{
    State &s = State::getSingleton();

    BreadFirstExpansion(food,
                        [&s, &food](const Location &l, int distance) {
                            Square &sq = s.getGrid(l);
                            if (sq.isWater || distance >= HELP_RADIUS)
                            {
                                return OBSTACLE;
                            }
                            else
                            {
                                sq.influence += (HELP_RADIUS - distance);
                                return CONTINUE;
                            }
                        });
}