#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include "character.h"
#include "camera.h"
#include "environment.h"
#include "game.h"
#include "input.h"
#include "utils.h"

const int DEFAULT_MAX_HP = 100;
const int DEFAULT_SPEED = 10;

Character character;

const float GRAVITY_FORCE = 98;
const int MAX_JUMP_FORCE_TIME_MS = 100;
const float JUMP_FORCE = 400;


void spawn_character(Level *lvl) {
	character.x_m = lvl->starting_point.x_m;
	character.y_m = lvl->starting_point.y_m;
	character.direction = 1;
	character.max_hp = DEFAULT_MAX_HP;
	character.current_hp = character.max_hp;
	character.w_m = 1;
	character.h_m = 2;
	character.color = (Color) {0xFF, 0x00, 0x00,};
	character.last_update_tick = SDL_GetTicks();
	character.x_speed_m = DEFAULT_SPEED;
	character.y_speed_m = 0;
	character.jumped = false;
	character.jump_finished = SDL_GetTicks();
	character.jump_start = character.jump_finished - 1;

	character.melee_attack_start_time = 0;
	character.melee_attack_cooldown_ms = 300;
	character.melee_attack_time_ms = 100;
	character.melee_attack_range_m = 2;
}

SDL_Rect get_character_rect(void) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(character.x_m, character.y_m, &x, &y);
	calculate_m_to_p_dimesions(character.w_m, character.h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_melee_weapon_rect(void) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	x_m = character.direction == 1 ? character.x_m + character.w_m : character.x_m - character.melee_attack_range_m;
	y_m = character.y_m + character.h_m * .5;
	w_m = character.melee_attack_range_m;
	h_m = .3;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_health_bar_border_rect(void) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	// TODO: Get rid of magic numbers
	w_m = character.w_m * 1.4; 
	h_m = .3;
	x_m = character.x_m - .2 *  character.w_m;
	y_m = character.y_m + character.h_m * 1.2;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}


SDL_Rect get_health_bar_background_rect(void) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	// TODO: Get rid of magic numbers
	w_m = character.w_m * 1.35; 
	h_m = .25;
	x_m = character.x_m - .175 *  character.w_m;
	y_m = character.y_m + character.h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_health_bar_indicator_rect(float hp_percentage) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	// TODO: Get rid of magic numbers
	w_m = character.w_m * 1.35 * hp_percentage; 
	h_m = .25;
	x_m = character.x_m - .175 *  character.w_m;
	y_m = character.y_m + character.h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

void update_character_state(Level *lvl) {
	Uint32 tick = SDL_GetTicks();
	int milliseconds_passed = tick - character.last_update_tick;
	if (milliseconds_passed >= UPDATE_TICK_RATE) {

		if (right_pressed) {
			character.x_m += (float) milliseconds_passed * character.x_speed_m  * .001;
			character.direction = 1;
		}
		if (left_pressed) {
			character.x_m -= (float) milliseconds_passed * character.x_speed_m * .001;
			character.direction = -1;
		}

		if (character.jumping && tick - character.jump_start <= MAX_JUMP_FORCE_TIME_MS) {
			character.y_speed_m += milliseconds_passed * JUMP_FORCE * .001;
		}
		

		character.y_speed_m -= GRAVITY_FORCE * milliseconds_passed * .001;
		character.y_m += character.y_speed_m * milliseconds_passed * .001;

		character.x_m = MIN(character.x_m, lvl->width_m - character.w_m);
		character.x_m = MAX(character.x_m, 0);
		character.y_m = MIN(character.y_m, lvl->height_m - character.h_m);
		character.y_m = MAX(character.y_m, 0);

		int blocks_len = lvl->blocks_len;

		float x_collision_m, y_collision_m;

		for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
			x_collision_m = 0, y_collision_m = 0;

			if (check_block_collision(block, &x_collision_m, &y_collision_m)) {
				if ((ABS(x_collision_m)) > (ABS(y_collision_m))) {
					character.y_m += y_collision_m;
					if (y_collision_m > 0) {
						character.y_speed_m = MAX(0, character.y_speed_m);
						character.jumped = false;
						character.jumped_twice = false;
					} else if (y_collision_m < 0) {
						character.y_speed_m = MIN(0, character.y_speed_m);
					}
				} else
					character.x_m += x_collision_m;

			}

		}

		character.last_update_tick = tick;
	}
}

void melee_attack(void) {
	Uint32 tick = SDL_GetTicks();
	if (tick - character.melee_attack_start_time >= character.melee_attack_cooldown_ms || character.melee_attack_start_time == 0) {
		character.melee_attack_start_time = tick;
	}
}

void start_jump(void) {
	if (character.jump_finished < character.jump_start)
		return;

	if (!character.jumped) {
		printf("Jump!\n");
		character.jumped = true;
		character.jumping = true;
		character.jump_start = SDL_GetTicks();
		character.y_speed_m = 0;
	} else if (!character.jumping && !character.jumped_twice) {
		printf("Double jump!\n");
		character.jumped_twice = true;
		character.jumping = true;
		character.jump_start = SDL_GetTicks();
		character.y_speed_m = 0;
	} else {
		printf("No triple jump allowed!\n");
	}
}

void finish_jump(void) {
	character.jumping = false;
	character.jump_finished = SDL_GetTicks();
}

void draw_health_bar(Level *lvl, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect border_rect = get_health_bar_border_rect();
	SDL_RenderFillRect(renderer, &border_rect);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_Rect background_rect = get_health_bar_background_rect();
	SDL_RenderFillRect(renderer, &background_rect);

	float hp_percentage = (float) character.current_hp / character.max_hp;
	SDL_SetRenderDrawColor(renderer, 0x00,  0xFF, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect indicator_rect = get_health_bar_indicator_rect(hp_percentage);
	SDL_RenderFillRect(renderer, &indicator_rect);
}

void draw_weapon(Level *lvl, SDL_Renderer *renderer) {
	Uint32 tick = SDL_GetTicks();
	if (tick - character.melee_attack_start_time <= character.melee_attack_time_ms) {
		SDL_SetRenderDrawColor(renderer, 0x5F, 0x5F, 0x7F, SDL_ALPHA_OPAQUE);
		SDL_Rect rect = get_melee_weapon_rect();
		SDL_RenderFillRect(renderer, &rect);
	}
}

void draw_character(Level *lvl, SDL_Renderer *renderer) {
	calculate_m_to_p_coefficients(lvl);

	SDL_Rect rect = get_character_rect();
	SDL_SetRenderDrawColor(renderer, character.color.R, character.color.G, character.color.B, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);

	draw_weapon(lvl, renderer);
	draw_health_bar(lvl, renderer);

}

