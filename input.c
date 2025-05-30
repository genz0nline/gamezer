#include <SDL2/SDL_keycode.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "character.h"
#include "camera.h"

#include "input.h"

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

void handle_keydown(SDL_Keycode sym) {
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
		case SDLK_MINUS:
			zoom_out();
			printf("Camera capture window width and height = %f, %f\n", capture_window_width_m, capture_window_height_m);
			break;
		case SDLK_EQUALS:
			zoom_in();
			printf("Camera capture window width and height = %f, %f\n", capture_window_width_m, capture_window_height_m);
			break;
	}
}

void handle_keyup(SDL_Keycode sym) {
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
