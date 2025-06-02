#ifndef CHARACTER_H
#define CHARACTER_H

#include "unit.h"
#include "environment.h"
#include "skills.h"
#include "classes.h"

typedef struct {
	Unit unit;

	Character_Class character_class;
	Skill *skills;

	bool jumped;
	bool jumped_twice;
	bool jumping;
	Uint32 jump_start;
	Uint32 jump_finished;

	Uint32 dash_start_tick;
	int dash_time_ms;
	float dash_speed_m;
	int dash_direction;
	int dash_cooldown_ms;
} Character;

extern Character character;

void spawn_character(Level *lvl, Character_Class character_class);
void update_character_state(Level *lvl);
void draw_character(SDL_Renderer *renderer, Level *lvl);
void start_jump(void);
void finish_jump(void);
void dash(void);
void die(void);

#endif
