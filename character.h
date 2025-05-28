#ifndef CHARACTER_H
#define CHARACTER_H

#include "environment.h"

typedef struct {
	float x_m, y_m;
	float w_m, h_m;
	Color color;
	int max_hp;
	int current_hp;
} Character;

extern Character character;

void spawn_character(Level *lvl);
void draw_character(Level *lvl, SDL_Surface *surface);

#endif
