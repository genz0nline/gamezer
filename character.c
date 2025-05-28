#include "character.h"
#include "camera.h"
#include <SDL2/SDL_surface.h>

const int DEFAULT_MAX_HP = 100;
Character character;

void spawn_character(Level *lvl) {
	character.x_m = lvl->starting_point.x_m;
	character.y_m = lvl->starting_point.y_m;
	character.max_hp = DEFAULT_MAX_HP;
	character.current_hp = character.max_hp;
	character.w_m = 0.6;
	character.h_m = 2;
	character.color = (Color) {0xFF, 0x00, 0x00,};
}

SDL_Rect get_character_rect(void) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(character.x_m, character.y_m, &x, &y);
	calculate_m_to_p_dimesions(character.w_m, character.h_m, &w, &h);
	SDL_Rect block_rect = {x, y, w, h};
	return block_rect;
}

void draw_character(Level *lvl, SDL_Surface *surface) {
	calculate_m_to_p_coefficients(lvl);

	SDL_Rect rect = get_character_rect();
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, character.color.R, character.color.G, character.color.B));
}

