#ifndef UNITS_H
#define UNITS_H

#include "game.h"

typedef struct {
	float x, y;
	float w, h;
} Unit;

void render_unit(Game *game, Unit *unit);

#endif // UNITS_H
