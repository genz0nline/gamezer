#include <SDL2/SDL.h>

#include "render.h"
#include "coordinate_transformation.h"
#include "blocks.h"
#include "instance.h"


void render_block(Game *game, Block *block) {
	SDL_Rect rect = get_rectangle(game, block->x, block->y, block->w, block->h);

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->renderer, &rect);
}

void render_section(Game *game, Section *section) {
	SDL_Rect background = get_rectangle(game, 0, 0, section->w, section->h);
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->renderer, &background);

	for (int i = 0; i < section->blocks_len; i++) {
		render_block(game, section->blocks + i);
	}
}

