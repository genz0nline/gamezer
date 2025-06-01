#ifndef CHARACTER_H
#define CHARACTER_H

#include "unit.h"
#include "environment.h"

typedef struct {
	Unit unit;

	Uint32 melee_attack_start_time;
	int melee_attack_damage;
	int melee_attack_cooldown_ms;
	int melee_attack_time_ms;
	float melee_attack_range_m;

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

void spawn_character(Level *lvl);
void update_character_state(Level *lvl);
void draw_character(SDL_Renderer *renderer, Level *lvl);
SDL_Rect get_melee_weapon_rect(void);
void start_jump(void);
void finish_jump(void);
void dash(void);
void melee_attack(void);
void die(void);

#endif
