#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "skills.h"
#include "character.h"
#include "environment.h"
#include "string.h"
#include "utils.h"

void initialize_skill_vicious_slash(Skill *skill) {

	char spell_name[] = "Visiour slash";

	skill->id = 1;
	skill->cast_type = CAST_TYPE_INSTANT;
	skill->attack_type = ATTACK_TYPE_INSTANT;
	skill->target_type = TARGET_TYPE_ENEMY;
	skill->resource = RESOURCE_FREE;
	skill->cost = 0;
	skill->damage = 55;
	skill->range_m = 2;
	skill->cooldown = 500;
	skill->cast_time = 0;
	skill->projectile_speed_m = 0;
	strncpy(skill->name, spell_name, (size_t) MAX_SPELL_NAME);

	skill->cast_started_tick = 0;
	skill->cast_finished_tick = 0;

}

void use_skill_on_mob(int index, Mob *target) {

	Skill *skill = character.skills + index;

	if (target->unit.dead) {
		printf("The target is dead\n");
		return;
	}

	if (skill->target_type != TARGET_TYPE_ENEMY) {
		printf("Wrong target\n");
		return;
	}

	if (character.unit.direction * (target->unit.x_m - character.unit.x_m) < 0) {
		printf("You have to face the target\n");
		return;
	}

	Uint32 tick = SDL_GetTicks();

	printf("%d, %d, %d\n", skill->cast_finished_tick, tick, skill->cooldown);

	if (skill->cast_finished_tick > 0 && tick - skill->cast_finished_tick < skill->cooldown) {
		printf("On cooldown\n");
		return;
	}

	Coordinate character_center = {
		.x_m = character.unit.x_m + character.unit.w_m * .5,
		.y_m = character.unit.y_m + character.unit.h_m * .5,
	};

	Coordinate mob_center = {
		.x_m = target->unit.x_m + target->unit.w_m * .5,
		.y_m = target->unit.y_m + target->unit.h_m * .5,
	};


	float distance_m = distance(character_center, mob_center);
	if (distance_m > skill->range_m) {
		printf("Too far away (%f > %f)\n", distance_m, skill->range_m);
		return;
	}

	switch (skill->cast_type) {
		case CAST_TYPE_INSTANT:
			switch (skill->attack_type) {
				case ATTACK_TYPE_INSTANT:
					printf("Attacking\n");
					target->unit.current_hp -= skill->damage;
					skill->cast_finished_tick = tick;
					break;
			}
			break;
	}
}

void intiialize_skill_from_resource() {
	return;
}
