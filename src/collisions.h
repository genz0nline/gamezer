#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdbool.h>
#include "units.h"


typedef struct Block Block;

typedef enum {
	AXIS_X,
	AXIS_Y,
	AXIS_NONE,
} Axis;

float check_collision(Unit *unit, Block *block, int milliseconds, Axis *axis);

#endif
