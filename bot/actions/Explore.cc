#include <climits>
#include "Explore.h"
#include "../algos/astar.h"
#include "../algos/bfs.h"
#include "../engine/State.h"
#include "../engine/Location.h"
#include "../debug.h"

#define WORST_INFLUENCE -999999
#define INFLUENCE_DISTANCE 30

const std::string actionName = "EXPLORE";

Explore::Explore(const Location &worker) : Action(worker)
{
  bestdir = IMPOSSIBLE;
  calculated = false;
}

bool Explore::canWork()
{
    if (calculated) {
      return bestdir != IMPOSSIBLE && worker.canWalkTo(bestdir);
    }

    State &s = State::getSingleton();
    double bestInfluence = WORST_INFLUENCE;
    Location bestLoc;

    BreadFirstExpansion(worker,
        [&s, &bestInfluence, &bestLoc, this](const Location &l, int distance) {
            Square &sq = s.getGrid(l);
            if (distance >= INFLUENCE_DISTANCE || sq.isWater)
            {
                return OBSTACLE;
            }
            else
            {
                double score = sq.influence;
                if (sq.isVisible) {
                  score += 30;
                }
                if (bestInfluence < score && l != worker) {
                    bestInfluence = score;
                    bestLoc = l;
                }
                return CONTINUE;
            }
        });
    

    calculated = true;    
    if (bestInfluence > WORST_INFLUENCE + 10) {
        Path p = AStar(worker, bestLoc);
        bestdir = p[0].origin;
        return worker.canWalkTo(bestdir);
    }
    return false;
}

void Explore::work()
{
    if (bestdir != IMPOSSIBLE)
    {
        worker.walkTo(bestdir);
    }
}

const std::string &Explore::actionName() const
{
    return ::actionName;
}