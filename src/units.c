#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "units.h"
#include "coordinate_transformation.h"

SDL_Rect get_unit_rect(Game *game, Unit *unit) {
	return get_rectangle(game, unit->x - .5 * unit->w, unit->y, unit->w, unit->h);
}

void render_unit(Game *game, Unit *unit) {
	SDL_Rect rect = get_unit_rect(game, unit);
	
	SDL_SetRenderDrawColor(game->renderer, 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->renderer, &rect);
}
