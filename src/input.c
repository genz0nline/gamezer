#include "input.h"
#include <SDL2/SDL_scancode.h>
#include <stdlib.h>
#include "game.h"
#include "units.h"

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

void press_button(Game *game, SDL_Scancode scancode) {
	switch (scancode) {
		case SDL_SCANCODE_LEFT:
			game->input->left_pressed = true;
			game->character->unit.direction = -1;
			break;
		case SDL_SCANCODE_RIGHT:
			game->input->right_pressed = true;
			game->character->unit.direction = 1;
			break;
		case SDL_SCANCODE_UP:
			character_start_jump(game->character);
			break;
		case SDL_SCANCODE_DOWN:
			game->input->down_pressed = true;
			break;
		case SDL_SCANCODE_MINUS:
			game->input->minus_pressed = true;
			break;
		case SDL_SCANCODE_EQUALS:
			game->input->equals_pressed = true;
			break;
		default:
			break;
	}
}

void unpress_button(Game *game, SDL_Scancode scancode) {
	switch (scancode) {
		case SDL_SCANCODE_LEFT:
			game->input->left_pressed = false;
			break;
		case SDL_SCANCODE_RIGHT:
			game->input->right_pressed = false;
			break;
		case SDL_SCANCODE_UP:
			character_finish_jump(game->character);
			break;
		case SDL_SCANCODE_DOWN:
			game->input->down_pressed = false;
			break;
		case SDL_SCANCODE_MINUS:
			game->input->minus_pressed = false;
			break;
		case SDL_SCANCODE_EQUALS:
			game->input->equals_pressed = false;
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
