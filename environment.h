#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>

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
	float width_m;
	float height_m;
	int blocks_len;
	Block *blocks;
	Coordinate starting_point;
} Level;

Level *initialize_default_level(void);
void free_level(Level *lvl);
void draw_default_level(Level *lvl, SDL_Renderer *renderer);
bool check_block_collision(Block *block, float *x_collision_m, float *y_collision_m);


#endif
