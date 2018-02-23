#ifndef EXPLORE_ACTION_H
#define EXPLORE_ACTION_H

#include "Action.h"
#include "../algos/Path.h"

class Explore : public Action
{
public:
  /**
   * Construir la acción explore
   */
  Explore(const Location &worker);
  bool canWork();
  void work();
  const std::string & actionName() const;
protected:
  FWDirection bestdir;
  bool calculated;
};

#endif