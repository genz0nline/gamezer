#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "character.h"
#include "camera.h"
#include "classes.h"
#include "environment.h"
#include "game.h"
#include "input.h"
#include "unit_func.h"

const int DEFAULT_MAX_HP = 100;
const int DEFAULT_SPEED = 10;

Character character;

const int MAX_JUMP_FORCE_TIME_MS = 100;
const float JUMP_FORCE = 400;

void spawn_character(Level *lvl, Character_Class character_class) {
	character.unit.x_m = lvl->starting_point.x_m;
	character.unit.y_m = lvl->starting_point.y_m;
	character.unit.direction = 1;
	character.unit.max_hp = DEFAULT_MAX_HP;
	character.unit.current_hp = character.unit.max_hp;
	character.unit.w_m = 1;
	character.unit.h_m = 2;
	character.unit.color = (Color) {0xFF, 0x00, 0x00,};
	character.unit.last_update_tick = SDL_GetTicks();
	character.unit.max_x_speed_m = DEFAULT_SPEED;
	character.unit.x_speed_m = 0;
	character.unit.y_speed_m = 0;
	character.jumped = false;
	character.jump_finished = SDL_GetTicks();
	character.jump_start = character.jump_finished - 1;

	character.dash_start_tick = 0;
	character.dash_time_ms = 200;
	character.dash_speed_m = 30;
	character.dash_direction = 1;
	character.dash_cooldown_ms = 400;

	character.unit.dead = false;

	character.character_class = character_class;

	switch (character_class) {
		case WARRIOR:
			character.skills = initialize_warrior_skills();
			break;
		default:
			break;
	}
}

SDL_Rect get_character_sprite_rect(void) {
	int x, y, w, h;
	calculate_m_to_p_dimesions(character.unit.h_m, character.unit.h_m, &w, &h);
	calculate_m_to_p_coordinates(character.unit.x_m - .5 * (character.unit.h_m - character.unit.w_m), character.unit.y_m, &x, &y);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_character_rect(void) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(character.unit.x_m, character.unit.y_m, &x, &y);
	calculate_m_to_p_dimesions(character.unit.w_m, character.unit.h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_health_bar_border_rect(void) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	w_m = character.unit.w_m * 1.4; 
	h_m = .3;
	x_m = character.unit.x_m - .2 *  character.unit.w_m;
	y_m = character.unit.y_m + character.unit.h_m * 1.2;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}


SDL_Rect get_health_bar_background_rect(void) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	w_m = character.unit.w_m * 1.35; 
	h_m = .25;
	x_m = character.unit.x_m - .175 *  character.unit.w_m;
	y_m = character.unit.y_m + character.unit.h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_health_bar_indicator_rect(float hp_percentage) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	w_m = character.unit.w_m * 1.35 * hp_percentage; 
	h_m = .25;
	x_m = character.unit.x_m - .175 *  character.unit.w_m;
	y_m = character.unit.y_m + character.unit.h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

void update_character_speed(Level *lvl, Uint32 tick, int milliseconds_passed) {
		// x-axis speed
		if (character.dash_start_tick != 0 && tick - character.dash_start_tick < character.dash_time_ms) {
			character.unit.x_speed_m = character.dash_direction * character.dash_speed_m;
		} else {
			if (right_pressed) {
				character.unit.direction = 1;
				character.unit.x_speed_m = character.unit.max_x_speed_m;
			} else if (left_pressed) {
				character.unit.direction = -1;
				character.unit.x_speed_m = -character.unit.max_x_speed_m;
			} else {
				character.unit.x_speed_m = 0;
			}
		}

		// y-axis speed
		if (character.jumping && tick - character.jump_start <= MAX_JUMP_FORCE_TIME_MS) {
			character.unit.y_speed_m += milliseconds_passed * JUMP_FORCE * .001;
		}
		character.unit.y_speed_m -= GRAVITY_FORCE * milliseconds_passed * .001;
}

void check_character_collision(Level *lvl) {
	bool landed;
	check_unit_collision(lvl, &character.unit, &landed);
	if (landed) {
		character.jumped = false;
		character.jumped_twice = false;
	}
}

void update_character_state(Level *lvl) {
	if (character.unit.current_hp <= 0) {
		character.unit.dead = true;
	}

	if (character.unit.dead)
		return;

	Uint32 tick = SDL_GetTicks();

	int milliseconds_passed = tick - character.unit.last_update_tick;
	if (milliseconds_passed >= UPDATE_TICK_RATE) {

		// calculate_update_character_speed
		update_character_speed(lvl, tick, milliseconds_passed);

		// calculate_new_position
		update_unit_position(lvl, &(character.unit), milliseconds_passed);
		
		// collisions
		check_character_collision(lvl);

		character.unit.last_update_tick = tick;
	}
}

void start_jump(void) {
	if (character.jump_finished < character.jump_start)
		return;

	if (!character.jumped) {
		character.jumped = true;
		if (character.unit.y_speed_m != 0)
			character.jumped_twice = true;
		character.jumping = true;
		character.jump_start = SDL_GetTicks();
		character.unit.y_speed_m = 0;
	} else if (!character.jumping && !character.jumped_twice) {
		character.jumped_twice = true;
		character.jumping = true;
		character.jump_start = SDL_GetTicks();
		character.unit.y_speed_m = 0;
	}
}

void finish_jump(void) {
	character.jumping = false;
	character.jump_finished = SDL_GetTicks();
}

void dash(void) {
	Uint32 tick = SDL_GetTicks();
	if (character.dash_start_tick == 0 || tick - character.dash_start_tick > character.dash_cooldown_ms) {
		character.dash_start_tick = tick;
		character.dash_direction = character.unit.direction;
	}
}

void draw_health_bar(Level *lvl, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect border_rect = get_health_bar_border_rect();
	SDL_RenderFillRect(renderer, &border_rect);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_Rect background_rect = get_health_bar_background_rect();
	SDL_RenderFillRect(renderer, &background_rect);

	float hp_percentage = (float) character.unit.current_hp / character.unit.max_hp;
	SDL_SetRenderDrawColor(renderer, 0x00,  0xFF, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect indicator_rect = get_health_bar_indicator_rect(hp_percentage);
	SDL_RenderFillRect(renderer, &indicator_rect);
}

void draw_character(SDL_Renderer *renderer, Level *lvl) {
	if (character.unit.dead)
		return;

	calculate_m_to_p_coefficients(lvl);
	
	SDL_Rect rect = get_character_sprite_rect();
	SDL_Surface *character_surface = IMG_Load("src/static/wizard_64x64.png");
	SDL_Texture *character_texture = SDL_CreateTextureFromSurface(renderer, character_surface);
	SDL_FreeSurface(character_surface);
	if (character.unit.direction == 1) 
		SDL_RenderCopy(renderer, character_texture, NULL, &rect);
	else
		SDL_RenderCopyEx(renderer, character_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);

	// SDL_SetRenderDrawColor(renderer, character.unit.color.R, character.unit.color.G, character.unit.color.B, SDL_ALPHA_OPAQUE);
	// SDL_RenderFillRect(renderer, &rect);

	draw_health_bar(lvl, renderer);
}

void die(void) {
	character.unit.current_hp = 0;
	character.unit.dead = true;
}

