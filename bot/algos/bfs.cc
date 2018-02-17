#include "bfs.h"

#include <queue>
#include <unordered_set>
#include <math.h>
#include "../engine/Location.h"
#include "../debug.h"

using namespace std;

void BreadFirstExpansion(const Location &origin, std::function<BFS(const Location &, int)> callback)
{
    State &s = State::getSingleton();

    queue<pair<Location, int>> nodes;
    unordered_set<Location> visited;

    nodes.push(make_pair(origin, 0));
    visited.insert(origin);

    while (nodes.size())
    {
        auto n = nodes.front();
        nodes.pop();
        BFS result = callback(n.first, n.second);
        if (result == CONTINUE || result == TARGET)
        {
            for (auto dir : FDIRECTIONS)
            {
                Location l(n.first, dir);
                l.wrap();
                if (!visited.count(l))
                {
                    visited.insert(l);
                    nodes.push(make_pair(l, n.second + 1));
                }
            }
        }
        if (result == TARGET)
        {
            return;
        }
    }
}

Path BreadFirstSearch(const Location &origin, std::function<BFS(const Location &, int)> callback)
{
    const State &s = State::getSingleton();
    queue<Step> nodes;
    unordered_set<Step> visited;
    Path path;

    nodes.push(Step({origin, IMPOSSIBLE, 0}));
    visited.insert(Step({origin, IMPOSSIBLE, 0}));

    while (nodes.size())
    {
        auto n = nodes.front();
        nodes.pop();
        for (auto dir : FDIRECTIONS)
        {
            Location l(n.point, dir);
            l.wrap();
            BFS result = callback(l, n.distance + 1);

            // Evitar obstáculos
            if (result != OBSTACLE)
            {
                Step st({l, OPPOSITE[dir], n.distance + 1});
                if (!visited.count(st))
                {
                    visited.insert(st);
                    nodes.push(st);

                    // Objetivo encontrado
                    if (result == TARGET)
                    {
                        Step &actSt = st;
                        while (actSt.origin != IMPOSSIBLE)
                        {
                            Location origin(st.point, st.origin);
                            origin.wrap();
                            path.push_back(st);
                            auto it = visited.find(Step({origin, IMPOSSIBLE}));
                            if (it == visited.end())
                            {
                                getDebugger() << "crash BFS" << origin << endl;
                            }
                            actSt = *it;
                        }
                        return path;
                    }
                }
            }
        }
    }
    return path;
}

Path findNearestFog(const Location &origin, int limit)
{
    const State &s = State::getSingleton();
    double realLimit = 2 * limit * limit + 2 * limit + 1;

    return BreadFirstSearch(origin, [&s](const Location & l, int distance) {
        if (s.getGrid(l).isWater) {
            return OBSTACLE;
        }
        if (!s.getGrid(l).isVisible) {
            return TARGET;
        }
        return CONTINUE;
    });
}

Path findNearestAnt(const Location &origin, int team)
{
    const State &s = State::getSingleton();

    return BreadFirstSearch(origin, [&s, &team](const Location & l, int distance) {
        if (s.getGrid(l).isWater) {
            return OBSTACLE;
        }
        if (s.getGrid(l).ant == team) {
            return TARGET;
        }
        return CONTINUE;
    });
}