#include "environment.h"
#include "camera.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>

const int DEFAULT_LEVEL_WIDTH_M = 40;
const int DEFAULT_LEVEL_HEIGHT_M = 30;

const int DEFAULT_BLOCK_HEIGHT_M = 2;

Level *initialize_default_level(void) {

	Block *blocks = (Block *)malloc(4 * sizeof(Block));

	blocks[0].x_m = 0;
	blocks[0].y_m = 0;
	blocks[0].width_m = DEFAULT_LEVEL_WIDTH_M;
	blocks[0].height_m = DEFAULT_BLOCK_HEIGHT_M;
	blocks[0].color = (Color){0, 0, 0,};

	blocks[1].x_m = 100;
	blocks[1].y_m = 100;
	blocks[1].width_m = 200;
	blocks[1].height_m = 20;
	blocks[1].color = (Color){0, 0, 0,};

	blocks[2].x_m = 350;
	blocks[2].y_m = 200;
	blocks[2].width_m = 200;
	blocks[2].height_m = 20;
	blocks[2].color = (Color){0, 0, 0,};

	blocks[3].x_m = 600;
	blocks[3].y_m = 100;
	blocks[3].width_m = 200;
	blocks[3].height_m = 20;
	blocks[3].color = (Color){0, 0, 0,};

	Level *lvl = (Level *)malloc(sizeof(Level));
	lvl->width_m = DEFAULT_LEVEL_WIDTH_M;
	lvl->height_m = DEFAULT_LEVEL_HEIGHT_M;
	lvl->blocks = blocks;
	lvl->blocks_len = 4;
	lvl->starting_point.x_m = 25;
	lvl->starting_point.y_m = 25;

	initialize_camera(lvl);

	return lvl;
}

void free_level(Level *lvl) {
	free(lvl->blocks);
	free(lvl);
}

SDL_Rect get_block_rect(Block *block) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(block->x_m, block->y_m, &x, &y);
	calculate_m_to_p_dimesions(block->width_m, block->height_m, &w, &h);
	SDL_Rect block_rect = {x, y, w, h};
	return block_rect;
}

void draw_default_level(Level *lvl, SDL_Surface *surface) {

	calculate_m_to_p_coefficients(lvl);

	int blocks_len = lvl->blocks_len;
	for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
		SDL_Rect rect = get_block_rect(block);
		SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, block->color.R, block->color.G, block->color.B));
	}
}


