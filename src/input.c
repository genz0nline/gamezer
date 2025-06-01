#include <SDL2/SDL_keycode.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "character.h"
#include "camera.h"
#include "input.h"
#include "game.h"
#include "main_menu.h"

bool left_pressed;
bool right_pressed;
bool up_pressed;
bool up_just_pressed;
bool down_pressed;

void initialize_input() {
	left_pressed = false;
	right_pressed = false;
	up_pressed = false;
	up_just_pressed = false;
	down_pressed = false;
}

void handle_in_play_keydown(SDL_Keycode sym, Game *game) {
	switch (sym) {
		case SDLK_RIGHT:
			right_pressed = true;
			break;
		case SDLK_LEFT:
			left_pressed = true;
			break;
		case SDLK_UP:
			start_jump();
			break;
		case SDLK_a:
			melee_attack();
			break;
		case SDLK_s:
			dash();
			break;
		case SDLK_ESCAPE:
			game->game_state=MAIN_MENU;
			break;
		case SDLK_MINUS:
			zoom_out();
			break;
		case SDLK_EQUALS:
			zoom_in();
			break;
	}
}

void handle_in_play_keyup(SDL_Keycode sym) {
	switch (sym) {
		case SDLK_RIGHT:
			right_pressed = false;
			break;
		case SDLK_LEFT:
			left_pressed = false;
			break;
		case SDLK_UP:
			finish_jump();
			break;
	}
}

void handle_main_menu_keydown(SDL_Keycode sym, Game *game) {
	switch (sym) {
		case SDLK_DOWN:
			highlighted_option_index += 1;
			highlighted_option_index %= main_menu_options_len;
			break;
		case SDLK_UP:
			if (highlighted_option_index == 0)
				highlighted_option_index = main_menu_options_len - 1;
			else 
				highlighted_option_index -= 1;
			break;
		case SDLK_RETURN:
			choose_main_menu_option(game);
			break;
	}
}
