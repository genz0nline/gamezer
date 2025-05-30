#ifndef CHARACTER_H
#define CHARACTER_H

#include "environment.h"

typedef struct {
	float x_m, y_m;
	float w_m, h_m;
	int direction; // 1 - looks right, -1 - looks left

	Uint32 melee_attack_start_time;
	int melee_attack_damage;
	int melee_attack_cooldown_ms;
	int melee_attack_time_ms;
	float melee_attack_range_m;

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

	Uint32 dash_start_tick;
	int dash_time_ms;
	Uint32 dash_speed;
	int dash_direction;
	int dash_cooldown_ms;

	bool dead;
} Character;

extern Character character;

void spawn_character(Level *lvl);
void update_character_state(Level *lvl);
void draw_character(Level *lvl, SDL_Renderer *renderer);
SDL_Rect get_melee_weapon_rect(void);
void start_jump(void);
void finish_jump(void);
void dash(void);
void melee_attack(void);
void die(void);

#endif
