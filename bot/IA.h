#ifndef IA_H
#define IA_H

#include "engine/Scheduler.h"
#include "engine/State.h"
#include "actions/Action.h"

class IA : public Scheduler {
public:
    void init();
    void finish();
};

#endif