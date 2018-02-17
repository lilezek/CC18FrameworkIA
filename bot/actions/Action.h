#ifndef ACTION_H
#define ACTION_H

#include "../engine/Location.h"

class Action
{
public:
  Action(const Location &worker);
  virtual bool canWork() = 0;
  virtual void work() = 0;
  virtual const std::string & actionName() const = 0;

  virtual ~Action() = 0;
protected:
  Location worker;
};

#endif