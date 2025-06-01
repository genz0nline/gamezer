#include <stdbool.h>

#include "unit_func.h"
#include "environment.h"
#include "utils.h"


void update_unit_position(Level *lvl, Unit *unit, int milliseconds_passed) {
	unit->x_m += unit->x_speed_m * milliseconds_passed * .001;
	unit->y_m += unit->y_speed_m * milliseconds_passed * .001;

	unit->x_m = MIN(unit->x_m, lvl->width_m - unit->w_m);
	unit->x_m = MAX(unit->x_m, 0);
	unit->y_m = MIN(unit->y_m, lvl->height_m - unit->h_m);
	unit->y_m = MAX(unit->y_m, 0);
}

bool check_unit_collision(Level *lvl, Unit *unit, bool *landed) {
	float x_collision_m, y_collision_m;
	int blocks_len = lvl->blocks_len;
	bool collisions_found = false;

	for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
		x_collision_m = 0, y_collision_m = 0;
		if (check_block_collision(unit, block, &x_collision_m, &y_collision_m)) {
			collisions_found = true;
			if ((ABS(x_collision_m)) > (ABS(y_collision_m))) {
				unit->y_m += y_collision_m;
				if (y_collision_m > 0) {
					unit->y_speed_m = MAX(0, unit->y_speed_m);
					if (landed != NULL)
						*landed = true;
				} else if (y_collision_m < 0) {
					unit->y_speed_m = MIN(0, unit->y_speed_m);
				}
			} else
				unit->x_m += x_collision_m;
		}
	}

	return collisions_found;
}
