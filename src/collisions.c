#include <math.h>
#include "collisions.h"
#include "utils.h"
#include "blocks.h"

float check_collision(Unit *unit, Block *block, int milliseconds, Axis *axis) {
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	float txEntry, txExit;
	float tyEntry, tyExit;

	float vx, vy;

	vx = unit->speed_x * milliseconds / 1000;
	vy = unit->speed_y * milliseconds / 1000;

	if (vx > .0) {
		dxEntry = block->x - (unit->x + unit->w);
		dxExit = block->x + block->w - unit->x;
	} else {
		dxEntry = block->x + block->w - unit->x;
		dxExit = block->x - (unit->x + unit->w); 
	}

	if (vy > .0) {
		dyEntry = block->y - (unit->y + unit->h);
		dyExit = block->y + block->h - unit->y;
	} else {
		dyEntry = block->y + block->h - unit->y;
		dyExit = block->y - (unit->y + unit->h); 
	}

	if (vx == .0) {
		if (unit->x + unit->w <= block->x || block->x + block->w <= unit->x)
			return 1.0f;
		txEntry = -INFINITY;
		txExit = INFINITY;
	} else {
		txEntry = dxEntry / vx;
		txExit = dxExit / vx;
	}

	if (vy == .0) {
		if (unit->y + unit->h <= block->y || block->y + block->h <= unit->y)
			return 1.0f;
		tyEntry = -INFINITY;
		tyExit = INFINITY;
	} else {
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;
	}

	float entryTime, exitTime;
	entryTime = MAX(txEntry, tyEntry);
	exitTime = MIN(txExit, tyExit);

	if (entryTime > exitTime || entryTime < 0.0f || entryTime > 1.0f)
		return 1.0f;

	if (txEntry > tyEntry) {
		*axis = AXIS_X;
	} else {
		*axis = AXIS_Y;
	}

	return entryTime;

}
