#ifndef UNITS_H
#define UNITS_H

#include "game.h"
#include <SDL2/SDL.h>

typedef struct {
	float x, y;
	float w, h;
	float max_speed_x;
	float speed_x;
	float speed_y;
	int direction;
	Uint32 last_update_tick;
} Unit;

void render_unit(Game *game, Unit *unit);
SDL_Rect get_unit_rect(Game *game, Unit *unit);

#endif // UNITS_H
