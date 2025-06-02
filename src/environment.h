#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>
#include "color.h"
#include "unit.h"
#include "utils.h"

#define MAX_MOBS							20
#define INITIAL_PROJECTILES_CAPACITY		20


typedef struct {
	float x_m;
	float y_m;
	float width_m;
	float height_m;
	Color color;
} Block;

typedef struct {
	Unit unit;

	float attack_range_m;
	float projectile_speed_m;
	float projectile_travel_distance_m;
	float projectile_width_m;
	float projectile_height_m;
	int projectile_damage;
	Color projectile_color;
	Uint32 last_fire_time;
	int fire_cooldown_ms;
} Mob;

typedef struct {
	float x_m, y_m;
	float x_speed_m;
	float w_m, h_m;
	int damage;
	float starting_point_x_m;
	float travel_distance_m;
	bool destroyed;
	Uint32 last_update_tick;
	Color color;
} Projectile;

typedef struct {
	float width_m;
	float height_m;
	int blocks_len;
	Block *blocks;
	Coordinate starting_point;
	Mob *mobs;
	int mobs_len;
	Projectile *projectiles;
	int projectiles_len;
	int projectiles_capacity;
} Level;

Level *initialize_default_level(void);
void update_environment_state(Level *lvl);
void free_level(Level *lvl);
void draw_default_level(SDL_Renderer *renderer, Level *lvl);
bool check_block_collision(Unit *unit, Block *block, float *x_collision_m, float *y_collision_m);


#endif
