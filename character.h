#ifndef CHARACTER_H
#define CHARACTER_H

#include "environment.h"
#include <SDL2/SDL_stdinc.h>

typedef struct {
	float x_m, y_m;
	float w_m, h_m;
	Color color;
	int max_hp;
	int current_hp;
	Uint32 last_update_tick;
	float x_speed_m;
	float y_speed_m;
	bool jumped;
	bool jumped_twice;
	bool jumping;
	Uint32 jump_start;
	Uint32 jump_finished;
} Character;

extern Character character;

void spawn_character(Level *lvl);
void update_character_position(Level *lvl);
void draw_character(Level *lvl, SDL_Surface *surface);
void start_jump(void);
void finish_jump(void);

#endif
