#include "render.h"
#include "coordinate_transformation.h"


void render_section(Game *game, Section *section, Camera *camera) {
	SDL_Rect background = get_rectangle(game, 0, 0, section->w, section->h);
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->renderer, &background);

	for (int i = 0; i < section->blocks_len; i++) {
		// render_block(game, section->blocks + i, camera);
	}
}

