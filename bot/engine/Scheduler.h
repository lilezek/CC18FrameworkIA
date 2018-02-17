#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "State.h"
#include <unordered_map>


class Scheduler {
public:
    virtual void init() = 0;
    virtual void finish() = 0;
};

#endif