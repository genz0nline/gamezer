#ifndef UNITS_H
#define UNITS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

typedef struct Unit {
	float x, y;
	float w, h;
	float max_speed_x;
	float speed_x;
	float speed_y;
	int direction;
	Uint32 last_update_tick;
} Unit;

typedef struct Character {
	Unit unit;
	bool jumped;
	bool jumped_twice;
	bool jumping;
	Uint32 jump_start_tick;
	Uint32 jump_finish_tick;
	int jump_force_max_duration;
	float jump_force;
} Character;

typedef struct Game Game;

void calculate_character_speed(Game *game);
void calculate_character_position(Game *game);
void calculate_unit_position(Game *game, Unit *unit, bool *landed);
void render_unit(Game *game, Unit *unit);
SDL_Rect get_unit_rect(Game *game, Unit *unit);
Character *initialize_character();
void cleanup_character(Character *character);
void character_start_jump(Character *character);
void character_finish_jump(Character *character);

#endif // UNITS_H
