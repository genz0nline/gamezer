#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>

#define MAX_MOBS	20

typedef struct {
	char R;
	char G;
	char B;
} Color;

typedef struct {
	float x_m;
	float y_m;
	float width_m;
	float height_m;
	Color color;
} Block;

typedef struct {
	float x_m, y_m;
} Coordinate;

typedef struct {
	float x_m, y_m;
	float w_m, h_m;
	int direction;
	Color color;
	int max_hp;
	int current_hp;
	Uint32 last_update_tick;
	float x_speed_m;
	float max_x_speed_m;
	float y_speed_m;

	float attack_range_m;

} Mob;

typedef struct {
	float width_m;
	float height_m;
	int blocks_len;
	Block *blocks;
	Coordinate starting_point;
	Mob *mobs;
	int mobs_len;
} Level;

Level *initialize_default_level(void);
void update_level_state(Level *lvl);
void free_level(Level *lvl);
void draw_default_level(Level *lvl, SDL_Renderer *renderer);
bool check_block_collision(Block *block, float *x_collision_m, float *y_collision_m);


#endif
