#include <climits>
#include "Random.h"
#include "../engine/State.h"
#include "../debug.h"

const std::string actionName = "RANDOM";

Random::Random(const Location &worker) : Action(worker)
{
}

bool Random::canWork()
{
  for (auto dir : FDIRECTIONS)
  {
    if (worker.canWalkTo(dir))
    {
      return true;
    }
  }
  return false;
}

void Random::work()
{
  std::vector<FWDirection> v;

  for (auto dir : FDIRECTIONS)
  {
    if (worker.canWalkTo(dir))
    {
      v.push_back(dir);
    }
  }


  if (v.size())
  {
    // TODO: No usar este random?
    size_t i = rand() % v.size();
    worker.walkTo(v[i]);
  }
  
}


const std::string & Random::actionName() const {
  return ::actionName;
}