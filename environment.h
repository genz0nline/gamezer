#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL_surface.h>

typedef struct {
	char R;
	char G;
	char B;
} Color;

typedef struct {
	int x;
	int y;
	int width;
	int height;
	Color color;
	// TODO: texture
} Block;

typedef struct {
	int width;
	int height;
	int blocks_len;
	Block *blocks;
} Level;

Level *initialize_default_level(void);
void free_level(Level *lvl);
void draw_default_level(Level *lvl, SDL_Surface *surface);

#endif
