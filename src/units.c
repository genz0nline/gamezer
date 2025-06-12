#include "units.h"
#include "coordinate_transformation.h"
#include "collisions.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include "math.h"

void calculate_character_speed(Game *game, Character *character) {
	character->unit.speed_x = game->input->right_pressed  ? character->unit.max_speed_x
		: game->input->left_pressed ? -character->unit.max_speed_x
		: 0;

	Uint32 tick = SDL_GetTicks();
	int milliseconds;

	if (game->input->up_pressed) {
		if (!character->jumped) {
			character->jump_start_tick = tick;
			character->jumped = true;
			character->unit.speed_y = 0;
		} else {
			printf("In jump\n");
			milliseconds = tick - character->jump_start_tick;
			if (milliseconds < character->jump_force_max_duration) {
				character->unit.speed_y += character->jump_force * milliseconds / 1000;
			}
			character->unit.speed_y -= GRAVITY;
		}
	} else {
		character->unit.speed_y -= GRAVITY;
	}

}

void calculate_character_position(Game *game, Character *character) {
	bool landed;
	calculate_unit_position(game, &character->unit, &landed);
	if (landed) {
		character->jumped = false;
	}
}

void calculate_unit_position(Game *game, Unit *unit, bool *landed) {
	Uint32 tick = SDL_GetTicks();
	int milliseconds = tick - unit->last_update_tick;

	int time_left = milliseconds;
	int max_iterations = 2;

	int blocks_len;
	float collision_time, min_collision_time;
	Axis collision_axis, block_collision_axis;
	*landed = false;
	while (time_left > 0.0 && max_iterations-- > 0) {
		blocks_len = game->instance->current_section->blocks_len;
		min_collision_time = INFINITY;
		collision_axis = AXIS_NONE;
		for (Block *block = game->instance->current_section->blocks; blocks_len-- > 0; block++) {
			collision_time = check_collision(unit, block, time_left, &block_collision_axis);
			if (.0 <= collision_time && collision_time < 1.0f) {
				if (collision_time < min_collision_time) {
					min_collision_time = collision_time;
					collision_axis = block_collision_axis;
				}
			}
		}

		if (0.0 <= min_collision_time && min_collision_time < 1.0f) {
			unit->x += unit->speed_x * time_left * min_collision_time / 1000;
			unit->y += unit->speed_y * time_left * min_collision_time / 1000;

			if (collision_axis == AXIS_X) {
				unit->speed_x = 0;
				unit->speed_y *= FRICTION;
			} else if (collision_axis == AXIS_Y) {
				if (unit->speed_y < 0)
					*landed = true;
				unit->speed_y = 0;
			}

			time_left -= time_left * min_collision_time;

		} else {
			unit->x += unit->speed_x * time_left / 1000;
			unit->y += unit->speed_y * time_left / 1000;
			time_left = 0.0;
		}
	}

	unit->last_update_tick = tick;
}

void render_unit(Game *game, Unit *unit) {
	SDL_Rect rect = get_unit_rect(game, unit);

	SDL_SetRenderDrawColor(game->renderer, 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->renderer, &rect);
}

SDL_Rect get_unit_rect(Game *game, Unit *unit) {
	return get_rectangle(game, unit->x, unit->y, unit->w, unit->h);
}

Character *initialize_character() {
	Character *character = (Character *)malloc(sizeof(Character));
	character->unit.x = 4;
	character->unit.y = 10;
	character->unit.w = 1;
	character->unit.h = 2;
	character->unit.speed_x = 0;
	character->unit.speed_y = 0;
	character->unit.max_speed_x = 15;
	character->unit.direction = 1;
	character->unit.last_update_tick = SDL_GetTicks();
	character->jumped = false;
	character->jump_force = 100;
	character->jump_start_tick = 0;
	character->jump_force_max_duration = 100;

	return character;
}

void cleanup_character(Character *character) {
	if (character == NULL)
		return;

	free(character);
}
