#ifndef SKILLS_H
#define SKILLS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

#include "environment.h"

#define MAX_SPELL_NAME		30

enum CAST_TYPES {
	CAST_TYPE_INSTANT,
	CAST_TYPE_CASTED,
	CAST_TYPE_CHANNELED,
};

enum ATTACK_TYPES {
	ATTACK_TYPE_PROJECTILE,
	ATTACK_TYPE_INSTANT,
};

enum RESOURCES {
	RESOURCE_FREE,
	RESOURCE_MANA,
	RESOURCE_RAGE,
};

enum TARGET_TYPE {
	TARGET_TYPE_ENEMY,
	TARGET_TYPE_FRIEND,
	TARGET_TYPE_DIRECTION,
};

typedef struct {
	int id;
	char name[MAX_SPELL_NAME];
	int damage;
	int cast_type;
	float range_m;
	int cast_time;
	int cooldown;
	int attack_type;
	float projectile_speed_m;
	int resource;
	int cost;
	int target_type;

	Uint32 cast_started_tick;
	Uint32 cast_finished_tick;

} Skill;

void initialize_skill_vicious_slash(Skill *skill);
void use_skill_on_mob(int index, Mob *target);

void intiialize_skill_from_resource();

#endif // SKILLS_H
