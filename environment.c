#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "environment.h"
#include "game.h"
#include "camera.h"
#include "utils.h"
#include "character.h"

const int DEFAULT_LEVEL_WIDTH_M = 40;
const int DEFAULT_LEVEL_HEIGHT_M = 30;

const int DEFAULT_BLOCK_HEIGHT_M = 2;

Level *initialize_default_level(void) {
	Level *lvl = (Level *)malloc(sizeof(Level));

	Block *blocks = (Block *)malloc(4 * sizeof(Block));
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

	Mob *mobs = (Mob *)malloc(MAX_MOBS * sizeof(Mob));
	lvl->mobs_len = 0;

	mobs[0].x_m = 30;
	mobs[0].y_m = 2;
	mobs[0].color = (Color) {0xFF, 0, 0xFF,};
	mobs[0].h_m = 2;
	mobs[0].w_m = 1;
	mobs[0].max_hp = 200;
	mobs[0].current_hp = 200;
	mobs[0].direction = -1;
	mobs[0].x_speed_m = 0;
	mobs[0].max_x_speed_m = 7;
	mobs[0].y_speed_m = 0;
	mobs[0].last_update_tick = SDL_GetTicks();
	mobs[0].attack_range_m = 7;
	mobs[0].projectile_speed_m = 15;
	mobs[0].projectile_damage = 23;
	mobs[0].projectile_travel_distance_m = 10;
	mobs[0].projectile_color = (Color) {0xFF, 0x20, 0x20};
	mobs[0].last_fire_time = 0;
	mobs[0].fire_cooldown_ms = 1000;
	mobs[0].dead = false;
	lvl->mobs_len++;

	Projectile *projectiles = (Projectile *)malloc(INITIAL_PROJECTILES_CAPACITY * sizeof(Projectile));
	lvl->projectiles_len = 0;

	lvl->width_m = DEFAULT_LEVEL_WIDTH_M;
	lvl->height_m = DEFAULT_LEVEL_HEIGHT_M;
	lvl->blocks = blocks;
	lvl->mobs = mobs;
	lvl->projectiles = projectiles;
	lvl->projectiles_capacity = INITIAL_PROJECTILES_CAPACITY;
	lvl->starting_point.x_m = 1;
	lvl->starting_point.y_m = DEFAULT_BLOCK_HEIGHT_M;

	initialize_camera(lvl);

	return lvl;
}

void free_level(Level *lvl) {
	free(lvl->blocks);
	free(lvl->mobs);
	free(lvl->projectiles);
	free(lvl);
}

SDL_Rect get_block_rect(Block *block) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(block->x_m, block->y_m, &x, &y);
	calculate_m_to_p_dimesions(block->width_m, block->height_m, &w, &h);
	SDL_Rect rect = {x, y-h, w, h};
	return rect;
}

SDL_Rect get_mob_rect(Mob *mob) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(mob->x_m, mob->y_m, &x, &y);
	calculate_m_to_p_dimesions(mob->w_m, mob->h_m, &w, &h);
	SDL_Rect rect = {x, y-h, w, h};
	return rect;
}

SDL_Rect get_projectile_rect(Projectile *projectile) {
	int x, y, w, h;
	calculate_m_to_p_coordinates(projectile->x_m, projectile->y_m, &x, &y);
	calculate_m_to_p_dimesions(projectile->w_m, projectile->h_m, &w, &h);
	SDL_Rect rect = {x, y-h, w, h};
	return rect;
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

SDL_Rect get_mob_health_bar_border_rect(Mob *mob) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	w_m = mob->w_m * 1.4; 
	h_m = .3;
	x_m = mob->x_m - .2 *  mob->w_m;
	y_m = mob->y_m + mob->h_m * 1.2;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_mob_health_bar_background_rect(Mob *mob) {
	int x, y, w, h;
	float x_m, y_m, w_m, h_m;
	w_m = mob->w_m * 1.35; 
	h_m = .25;
	x_m = mob->x_m - .175 *  mob->w_m;
	y_m = mob->y_m + mob->h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

SDL_Rect get_mob_health_bar_indicator_rect(Mob *mob) {
	int x, y, w, h;
	float hp_percentage = (float) mob->current_hp / mob->max_hp;
	float x_m, y_m, w_m, h_m;
	w_m = mob->w_m * 1.35 * hp_percentage; 
	h_m = .25;
	x_m = mob->x_m - .175 *  mob->w_m;
	y_m = mob->y_m + mob->h_m * 1.2 + .025;
	calculate_m_to_p_coordinates(x_m, y_m, &x, &y);
	calculate_m_to_p_dimesions(w_m, h_m, &w, &h);
	SDL_Rect block_rect = {x, y-h, w, h};
	return block_rect;
}

void add_projectile(Level *lvl, Projectile projectile) {
	if (lvl->projectiles_len == lvl->projectiles_capacity) {
		lvl->projectiles = (Projectile *)realloc(lvl->projectiles, lvl->projectiles_capacity * 2 * sizeof(Projectile));
		lvl->projectiles_capacity *= 2;
	}
	lvl->projectiles[lvl->projectiles_len++] = projectile;
}

void fire_range_attack(Level *lvl, Mob *mob) {
	if (character.dead)
		return;

	float w_m = .2;
	float h_m = .2;
	float x_m = mob->direction == 1 ? mob->x_m + mob->w_m : mob->x_m - w_m;
	Projectile projectile = {
		.w_m = w_m,
		.h_m = h_m,
		.x_m = x_m,
		.y_m = mob->y_m + mob->h_m * .6,
		.damage = mob->projectile_damage,
		.x_speed_m = mob->direction == 1 ? mob->projectile_speed_m : -mob->projectile_speed_m,
		.starting_point_x_m = x_m,
		.destroyed = false,
		.color = mob->projectile_color,
		.last_update_tick = SDL_GetTicks(),
		.travel_distance_m = mob->projectile_travel_distance_m,
	};

	add_projectile(lvl, projectile);
}

void update_mob_state(Level *lvl, Mob *mob) {
	if (mob->dead)
		return;
	Uint32 tick = SDL_GetTicks();
	int milliseconds_passed = tick - mob->last_update_tick;
	if (milliseconds_passed > UPDATE_TICK_RATE) {
		float distance = mob->x_m  + mob->w_m * .5 - character.x_m - character.w_m * .5;
		mob->direction = distance < 0 ? 1 : -1;
		if (ABS(distance) > mob->attack_range_m) {
			mob->x_speed_m = distance < 0 ? mob->max_x_speed_m : -mob->max_x_speed_m;
		} else if (ABS(distance) <= mob->attack_range_m * .85) {
			mob->x_speed_m = 0;
		}


		if (mob->x_speed_m == 0 && (mob->last_fire_time == 0 || (tick - mob->last_fire_time >= mob->fire_cooldown_ms))) {
			fire_range_attack(lvl, mob);
			mob->last_fire_time = tick;
		}

		mob->x_m += mob->x_speed_m * milliseconds_passed * .001;

		mob->x_m = MIN(mob->x_m, lvl->width_m - mob->w_m);
		mob->x_m = MAX(mob->x_m, 0);
		mob->y_m = MIN(mob->y_m, lvl->height_m - mob->h_m);
		mob->y_m = MAX(mob->y_m, 0);

		mob->last_update_tick = tick;
	}
}

bool check_projectile_hit_character(Projectile *projectile) {
	if (projectile->x_m > character.x_m + character.w_m)
		return false;
	if (projectile->x_m + projectile->w_m < character.x_m)
		return false;
	if (projectile->y_m > character.y_m + character.h_m)
		return false;
	if (projectile->y_m + projectile->h_m <  character.y_m)
		return false;

	return true;
}

void update_projectile_state(Level *lvl, Projectile *projectile) {
	if (projectile->destroyed) 
		return;

	Uint32 tick = SDL_GetTicks();
	int milliseconds_passed = tick - projectile->last_update_tick;
	if (milliseconds_passed > UPDATE_TICK_RATE) {
		projectile->x_m += projectile->x_speed_m * milliseconds_passed * .001;

		if (projectile->x_m <= 0 || projectile->x_m >= lvl->width_m - projectile->w_m)
			projectile->destroyed = true;

		float distance = ABS(projectile->x_m - projectile->starting_point_x_m);
		if (distance >= projectile->travel_distance_m)
			projectile->destroyed = true;

		if (check_projectile_hit_character(projectile)) {
			projectile->destroyed = true;
			character.current_hp -= projectile->damage;
			if (character.current_hp <= 0) {
				die();
			}
		}

		projectile->x_m = MIN(projectile->x_m, lvl->width_m - projectile->w_m);
		projectile->x_m = MAX(projectile->x_m, 0);
		projectile->y_m = MIN(projectile->y_m, lvl->height_m - projectile->h_m);
		projectile->y_m = MAX(projectile->y_m, 0);

		projectile->last_update_tick = tick;
	}
}

bool attack_hits(Mob *mob) {
	SDL_Rect weapon_rect = get_melee_weapon_rect();
	SDL_Rect mob_rect = get_mob_rect(mob);

	if (weapon_rect.x > mob_rect.x + mob_rect.w)
		return false;
	if (mob_rect.x > weapon_rect.x + weapon_rect.w)
		return false;
	if (weapon_rect.y > mob_rect.y + mob_rect.h)
		return false;
	if (mob_rect.y > weapon_rect.y + weapon_rect.h)
		return false;

	return true;
}

void deal_damage(Level *lvl) {
	Uint32 tick = SDL_GetTicks();

	if (tick - character.melee_attack_start_time <= character.melee_attack_time_ms) {
		int mobs_len = lvl->mobs_len;
		for (Mob *mob = lvl->mobs; --mobs_len >= 0; mob++) {
			if (attack_hits(mob)) {
				mob->current_hp -= character.melee_attack_damage;
				if (mob -> current_hp <= 0)
					mob->dead = true;
			}
		}
	}
}

void update_level_state(Level *lvl) {
	int mobs_len = lvl->mobs_len;
	for (Mob *mob = lvl->mobs; --mobs_len >= 0; mob++) {
		update_mob_state(lvl, mob);
	}

	int projectil_len = lvl->projectiles_len;
	for (Projectile *projectile = lvl->projectiles; --projectil_len >= 0; projectile++) {
		update_projectile_state(lvl, projectile);
	}

	deal_damage(lvl);
}

void draw_mob_health_bar(SDL_Renderer *renderer, Mob *mob) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect border_rect = get_mob_health_bar_border_rect(mob);
	SDL_RenderFillRect(renderer, &border_rect);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_Rect background_rect = get_mob_health_bar_background_rect(mob);
	SDL_RenderFillRect(renderer, &background_rect);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect indicator_rect = get_mob_health_bar_indicator_rect(mob);
	SDL_RenderFillRect(renderer, &indicator_rect);
}


void draw_mob(SDL_Renderer *renderer, Mob *mob) {
	if (mob->dead)
		return;
	SDL_Rect rect = get_mob_rect(mob);
	SDL_SetRenderDrawColor(renderer, mob->color.R, mob->color.G, mob->color.B, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);

	draw_mob_health_bar(renderer, mob);
}

void draw_projectile(SDL_Renderer *renderer, Projectile *projectile) {
	if (projectile->destroyed)
		return;

	SDL_Rect rect = get_projectile_rect(projectile);
	SDL_SetRenderDrawColor(renderer, projectile->color.R, projectile->color.G, projectile->color.B, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}

void draw_default_level(Level *lvl, SDL_Renderer *renderer) {

	calculate_m_to_p_coefficients(lvl);

	int blocks_len = lvl->blocks_len;
	for (Block *block = lvl->blocks; --blocks_len >= 0; block++) {
		SDL_Rect rect = get_block_rect(block);
		SDL_SetRenderDrawColor(renderer, block->color.R, block->color.G, block->color.B, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}

	int mobs_len = lvl->mobs_len;
	for (Mob *mob = lvl->mobs; --mobs_len >= 0; mob++) {
		draw_mob(renderer, mob);
	}

	int projectiles_len = lvl->projectiles_len;
	for (Projectile *projectile = lvl->projectiles; --projectiles_len >= 0; projectile++) {
		draw_projectile(renderer, projectile);
	}

}


