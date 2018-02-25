#include "IA.h"
#include "actions/GoTo.h"
#include "actions/Random.h"
#include "actions/Explore.h"
#include "algos/bfs.h"
#include "algos/Antgroup.h"
#include <climits>
#include "algos/minimax.h"

using namespace std;

BFS nearestAntNoDanger(const Location & l, int distance) {
    State & state = State::getSingleton();

    if (state.getGrid(l).ant == 0) {
        return TARGET;
    }

    if (state.getGrid(l).isWater || state.getGrid(l).enemyPresence.size()) {
        return OBSTACLE;
    }

    return CONTINUE;
}

void IA::init()
{
    unordered_map<Location, Action *> actions;

    State &s = State::getSingleton();

    // Darle órdenes a las hormigas para atacar hormigueros
    for (auto hill : s.enemyHills)
    {
        Path nearestAnt = BreadFirstSearch(hill, nearestAntNoDanger);
        if (nearestAnt.size() >= 1)
        {
            Location &ant = nearestAnt[0].point;
            int distance = INT_MAX;
            if (actions[ant] != nullptr && actions[ant]->actionName() == "GOTO")
            {
                distance = ((GoTo *)(actions[ant]))->getDistance();
            }
            if (distance > nearestAnt.size())
            {
                getDebugger() << "raiding hill " << hill << " with " << ant << endl;
                delete actions[ant];
                GoTo *action = new GoTo(ant, nearestAnt);
                actions[ant] = action;
            }
        }
    }

    // Darle órdenes a las hormigas para buscar comida
    for (auto food : s.food)
    {
        Path nearestAnt = BreadFirstSearch(food, nearestAntNoDanger);
        if (nearestAnt.size() >= 1)
        {
            Location &ant = nearestAnt[0].point;
            int distance = INT_MAX;
            if (actions[ant] != nullptr && actions[ant]->actionName() == "GOTO")
            {
                distance = ((GoTo *)(actions[ant]))->getDistance();
            }
            if (distance > nearestAnt.size())
            {
                getDebugger() << "getting food " << food << " with " << ant << endl;                
                delete actions[ant];
                GoTo *action = new GoTo(ant, nearestAnt);
                actions[ant] = action;
            }
        }
    }

    // Al resto que luche, huya o explore
    for (Location &ant : s.myAnts)
    {
        if (actions[ant] == nullptr)
        {
            getDebugger() << "General purpose ant: " << ant << endl;
            Square &sq = s.getGrid(ant);
            if (sq.enemyPresence.size())
            {
                getDebugger() << "Enemy presence" << endl;
                AntGroup ag = AntGroup::getGroupBattleAt(ant, 9);
                getDebugger() << "Group Battle " << ag.size() << endl;
                auto own = ag.getOwnAnts();
                auto enemy = ag.getEnemyAnts();
                if (own.size() != 0 && enemy.size() != 0)
                {
                    auto d = minimax(own, enemy);
                    getDebugger() << s.timer.getTime() << "ms" << endl;
                    getDebugger() << "Decision made " << d.size() << endl;

                    for (const Decision &dec : d)
                    {
                        getDebugger() << "The Ant " << dec.ant << " to " << dec.to << endl;

                        const Location &ant = dec.ant;

                        getDebugger() << "Location post" << endl;

                        if (actions[ant] == nullptr)
                        {
                            actions[ant] = new GoTo(ant, dec.to);
                        }
                        else
                        {
                            getDebugger() << "Busy ant" << endl;
                        }
                    }
                }
            }
            else
            {
                // Explorar si es posbile
                actions[ant] = new Explore(ant);
                // if (actions[ant]->canDo()) {
                //     actions[ant]->next();
                // } else {
                //     delete actions[ant];
                //     actions[ant] = new Random(ant);
                //     if (actions[ant]->canDo()) {
                //         actions[ant]->next();
                //     }
                // }
            }
        }
    }

    int moved = 1;
    while (moved)
    {
        getDebugger() << "Try" << endl;
        moved = 0;
        for (auto it = actions.begin(); it != actions.end(); it++)
        {
            if (it->second && it->second->canWork())
            {
                getDebugger() << "next" << endl;
                moved++;
                it->second->work();
                delete it->second;
                it->second = nullptr;
            }
        }
    }

    getDebugger() << "Deleting" << endl;
    for (auto &p : actions)
    {
        if (p.second)
        {
            delete p.second;
        }
    }
}

void IA::finish()
{
}
