#include "environment.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>

const int DEFAULT_LEVEL_WIDTH = 900;
const int DEFAULT_LEVEL_HEIGHT = 600;

const int DEFAULT_BLOCK_HEIGHT = 20;

Level *initialize_default_level(void) {

	Block *blocks = (Block *)malloc(4 * sizeof(Block));
	blocks[0].x = 0;
	blocks[0].y = 0;
	blocks[0].width = DEFAULT_LEVEL_WIDTH;
	blocks[0].height = DEFAULT_BLOCK_HEIGHT;
	blocks[0].color = (Color){0, 0, 0,};

	blocks[1].x = 100;
	blocks[1].y = 100;
	blocks[1].width = 200;
	blocks[1].height = 20;
	blocks[1].color = (Color){0, 0, 0,};

	blocks[2].x = 350;
	blocks[2].y = 200;
	blocks[2].width = 200;
	blocks[2].height = 20;
	blocks[2].color = (Color){0, 0, 0,};

	blocks[3].x = 600;
	blocks[3].y = 100;
	blocks[3].width = 200;
	blocks[3].height = 20;
	blocks[3].color = (Color){0, 0, 0,};

	Level *lvl = (Level *)malloc(sizeof(Level));
	lvl->width = DEFAULT_LEVEL_WIDTH;
	lvl->height = DEFAULT_LEVEL_HEIGHT;
	lvl->blocks = blocks;
	lvl->blocks_len = 4;
	
	return lvl;
}

void free_level(Level *lvl) {
	free(lvl->blocks);
	free(lvl);
}

void draw_default_level(Level *lvl, SDL_Surface *surface) {
	int blocks_len = lvl->blocks_len;
	for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
		SDL_Rect rect = {block->x, DEFAULT_LEVEL_HEIGHT - block->y - block->height, block->width, block->height};
		SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, block->color.R, block->color.G, block->color.B));
	}
}


