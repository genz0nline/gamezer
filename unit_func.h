#ifndef UNIT_FUNC_H
#define UNIT_FUNC_H

#include "environment.h"

void update_unit_position(Level *lvl, Unit *unit, int milliseconds_passed);
bool check_unit_collision(Level *lvl, Unit *unit, bool *landed);

#endif // UNIT_FUNC_H
