#ifndef UNITS_H
#define UNITS_H

#include <SDL2/SDL.h>

typedef struct CharacterClass CharacterClass;

typedef struct Unit {
	float x, y;
	float w, h;
	float max_speed_x;
	float speed_x;
	float speed_y;
	int direction;
	Uint32 last_update_tick;
	int sprite_id;
	SDL_Texture *texture;
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
	CharacterClass *character_class;
} Character;

typedef struct Game Game;

void calculate_character_speed(Game *game);
void calculate_character_position(Game *game);
void calculate_unit_position(Game *game, Unit *unit, bool *landed);
void render_unit(Game *game, Unit *unit);
SDL_Rect get_unit_texture_rext(Game *game, Unit *unit);
SDL_Rect get_unit_rect(Game *game, Unit *unit);
Character *initialize_character(Game *game, int class_id);
void cleanup_character(Character *character);
void character_start_jump(Character *character);
void character_finish_jump(Character *character);

#endif // UNITS_H
