#ifndef GOTO_ACTION_H
#define GOTO_ACTION_H

#include "Action.h"
#include "../algos/Path.h"
#include "../engine/Location.h"

class GoTo: public Action {
public:

    GoTo() = delete;
    GoTo(const Location &) = delete; 

    GoTo(const Location & ant, FWDirection target);
    GoTo(const Location & ant, const Path & target);

    bool canWork();
    void work();
    const std::string & actionName() const;
    int getDistance();
protected:
    FWDirection target;
    int distance;
};

#endif