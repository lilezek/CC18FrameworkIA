#ifndef RANDOM_ACTION_H
#define RANDOM_ACTION_H

#include "Action.h"

class Random : public Action
{
public:
  /**
   * Construir la acción random
   */
  Random(const Location &worker);
  /**
   * Construir la acción random, pero solo para andar aleatoriamente `times` veces
   */
  Random(const Location &worker, int times);
  bool canWork();
  void work();
  const std::string & actionName() const;
protected:
  int times;
};

#endif