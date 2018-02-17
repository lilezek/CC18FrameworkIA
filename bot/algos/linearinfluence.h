#ifndef LINEAR_INFLUENCE_H
#define LINEAR_INFLUENCE_H

#include "../engine/Location.h"

void antInfluence(const Location & ant);
void hillInfluence(const Location & hill);
void foodInfluence(const Location & food);

#endif