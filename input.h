#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "environment.h"
#include "game.h"

extern bool left_pressed;
extern bool right_pressed;
extern bool up_pressed;
extern bool up_just_pressed;
extern bool down_pressed;

void initialize_input();
void handle_in_play_keydown(SDL_Keycode sym, Game *game);
void handle_in_play_keyup(SDL_Keycode sym);
void handle_main_menu_keydown(SDL_Keycode sym, Game *game);
void handle_main_menu_keyup(SDL_Keycode sym);

#endif
