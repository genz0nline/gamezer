#ifndef UNIT_H
#define UNIT_H

#include <SDL2/SDL.h>

#include "color.h"

typedef struct {
	float x_m, y_m;
	float w_m, h_m;
	int direction; // 1 - looks right, -1 - looks left

	Color color;
	int max_hp;
	int current_hp;
	Uint32 last_update_tick;
	float x_speed_m;
	float max_x_speed_m;
	float y_speed_m;

	bool dead;
} Unit;

#endif // UNIT_H
