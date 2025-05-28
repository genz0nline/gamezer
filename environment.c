#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>
#include <stdbool.h>
#include "environment.h"
#include "camera.h"
#include "character.h"
#include "utils.h"

const int DEFAULT_LEVEL_WIDTH_M = 40;
const int DEFAULT_LEVEL_HEIGHT_M = 30;

const int DEFAULT_BLOCK_HEIGHT_M = 2;

Level *initialize_default_level(void) {

	Block *blocks = (Block *)malloc(4 * sizeof(Block));
	Level *lvl = (Level *)malloc(sizeof(Level));

	lvl->blocks_len = 0;

	blocks[0].x_m = 0;
	blocks[0].y_m = 0;
	blocks[0].width_m = DEFAULT_LEVEL_WIDTH_M;
	blocks[0].height_m = DEFAULT_BLOCK_HEIGHT_M;
	blocks[0].color = (Color){0, 0, 0,};
	lvl->blocks_len++;

	blocks[1].x_m = 20;
	blocks[1].y_m = 8;
	blocks[1].width_m = 2;
	blocks[1].height_m = 4;
	blocks[1].color = (Color){0, 0, 0xFF,};
	lvl->blocks_len++;

	// blocks[2].x_m = 350;
	// blocks[2].y_m = 200;
	// blocks[2].width_m = 200;
	// blocks[2].height_m = 20;
	// blocks[2].color = (Color){0, 0, 0xFF,};
	// lvl->blocks_len++;

	// blocks[3].x_m = 600;
	// blocks[3].y_m = 100;
	// blocks[3].width_m = 200;
	// blocks[3].height_m = 20;
	// blocks[3].color = (Color){0, 0, 0,};
	// lvl->blocks_len++;

	lvl->width_m = DEFAULT_LEVEL_WIDTH_M;
	lvl->height_m = DEFAULT_LEVEL_HEIGHT_M;
	lvl->blocks = blocks;
	lvl->starting_point.x_m = 1;
	lvl->starting_point.y_m = DEFAULT_BLOCK_HEIGHT_M;

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
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

bool check_block_collision(Block *block, float *x_collision_m, float *y_collision_m) {

	if (character.x_m + character.w_m < block->x_m)
		return false;
	if (character.x_m > block->x_m + block->width_m)
		return false;
	if (character.y_m + character.h_m < block->y_m)
		return false;
	if (character.y_m > block->y_m + block->height_m)
		return false;

	// In case of collision we have to push character back a little bit
	if ((2 * character.x_m + character.w_m) <= (2 * block->x_m + block->width_m)) {
		*x_collision_m = block->x_m - character.x_m - character.w_m;
	} else {
		*x_collision_m = block->x_m + block->width_m - character.x_m;
	}

	if ((2 * character.y_m + character.h_m) <= (2 * block->y_m + block->height_m)) {
		*y_collision_m = block->y_m - character.y_m - character.h_m;
	} else {
		*y_collision_m = block->y_m + block->height_m - character.y_m;
	}

	return true;
}

void draw_default_level(Level *lvl, SDL_Surface *surface) {

	calculate_m_to_p_coefficients(lvl);

	int blocks_len = lvl->blocks_len;
	for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
		SDL_Rect rect = get_block_rect(block);
		SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, block->color.R, block->color.G, block->color.B));
	}
}


