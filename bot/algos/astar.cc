#include "astar.h"
#include "../engine/State.h"

#include "unordered_map"
#include <climits>
#include <utility>

using namespace std;

Path reconstruct_path(const unordered_map<Location, FWDirection> &cameFrom, const Location &c)
{
    State &s = State::getSingleton();

    Path total_path;
    auto current = c;
    while (cameFrom.count(current))
    {
        auto currentDir = cameFrom.at(current);
        total_path.push_back(Step{current, currentDir});
        current = Location(current, currentDir);
        current.wrap();
    }

    return total_path;
}

Path AStarCustom(const Location &goal,
                 const Location &start,
                 std::function<int(const Location &l)> h,
                 std::function<BFS(const Location &, int)> callback)
{
    State &s = State::getSingleton();

    // The set of nodes already evaluated
    unordered_set<Location> closedSet;

    // Nota: se usan puntuaciones negativas en la cola de prioridad 
    // para ordenar del revés.
    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    priority_queue<pair<int, Location>> openSet;
    int fScore = h(start);
    openSet.push(make_pair(-fScore, start));

    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    unordered_map<Location, FWDirection> cameFrom;

    // For each node, the cost of getting from the start node to that node.
    unordered_map<Location, int> gScore;

    // The cost of going from start to start is zero.
    gScore[start] = 0;

    while (openSet.size())
    {
        auto node = openSet.top();
        openSet.pop();
        auto current = node.second;
        if (current == goal)
        {
            return reconstruct_path(cameFrom, current);
        }

        closedSet.insert(current);

        for (FWDirection dir : FDIRECTIONS)
        {
            Location neighbor(current, dir);
            neighbor.wrap();


            if (closedSet.count(neighbor))
            {
                continue; // Ignore the neighbor which is already evaluated.
            }

            // The distance from start to a neighbor is plus 1
            auto tentative_gScore = gScore[current] + 1;
            int neighbor_gScore;
            if (gScore.count(neighbor))
            {
                neighbor_gScore = gScore[neighbor];
            }
            else
            {
                neighbor_gScore = INT_MAX;
            }
            if (tentative_gScore >= neighbor_gScore)
                continue; // This is not a better path.

            BFS result = callback(neighbor, tentative_gScore);
            if (result == OBSTACLE)
            { // Ignorar obstáculos
                continue;
            }

            // This path is the best until now. Record it!
            cameFrom[neighbor] = OPPOSITE[dir];
            gScore[neighbor] = tentative_gScore;
            openSet.push(make_pair(-gScore[neighbor] - h(neighbor), neighbor));
        }
    }
    return Path();
}

Path AStar(const Location &goal, const Location &start)
{
    State &s = State::getSingleton();

    auto heuristic = [&s, &goal](const Location &l) {
        return s.distance2(l, goal);
    };

    auto obstacles = [&s](const Location &l, int tentative_distance) {
        return s.getGrid(l).isWater ? OBSTACLE : CONTINUE;
    };

    return AStarCustom(goal, start, heuristic, obstacles);
}