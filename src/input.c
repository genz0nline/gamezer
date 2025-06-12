#include "input.h"
#include <SDL2/SDL_scancode.h>
#include <stdlib.h>

Input *initialize_input(void) {
	Input *input = (Input *)malloc(sizeof(Input));

	input->left_pressed = false;
	input->right_pressed = false;
	input->up_pressed = false;
	input->down_pressed = false;
	input->minus_pressed = false;
	input->equals_pressed = false;

	return input;
}

void press_button(Input *input, SDL_Scancode scancode) {
	switch (scancode) {
		case SDL_SCANCODE_LEFT:
			input->left_pressed = true;
			break;
		case SDL_SCANCODE_RIGHT:
			input->right_pressed = true;
			break;
		case SDL_SCANCODE_UP:
			input->up_pressed = true;
			break;
		case SDL_SCANCODE_DOWN:
			input->down_pressed = true;
			break;
		case SDL_SCANCODE_MINUS:
			input->minus_pressed = true;
			break;
		case SDL_SCANCODE_EQUALS:
			input->equals_pressed = true;
			break;
		default:
			break;
	}
}

void unpress_button(Input *input, SDL_Scancode scancode) {
	switch (scancode) {
		case SDL_SCANCODE_LEFT:
			input->left_pressed = false;
			break;
		case SDL_SCANCODE_RIGHT:
			input->right_pressed = false;
			break;
		case SDL_SCANCODE_UP:
			input->up_pressed = false;
			break;
		case SDL_SCANCODE_DOWN:
			input->down_pressed = false;
			break;
		case SDL_SCANCODE_MINUS:
			input->minus_pressed = false;
			break;
		case SDL_SCANCODE_EQUALS:
			input->equals_pressed = false;
			break;
		default:
			break;
	}
}

void cleanup_input(Input *input) {
	if (input == NULL)
		return;

	free(input);
}
