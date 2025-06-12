#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "input.h"
#include "instance.h"
#include "render.h"
#include "game.h"
#include "camera.h"
#include "units.h"

const char *title = "Gamezer";
const int IMG_INIT_FLAGS = IMG_INIT_PNG;

void cleanup_game(Game *game, int error_code) {
	cleanup_input(game->input);
	free_camera(game->camera);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error_code);
}

void initialize_game(Game *game) {

	game->screen_width = DEFAULT_SCREEN_WIDTH;
	game->screen_height = DEFAULT_SCREEN_HEIGHT;
	game->window = NULL;
	game->renderer = NULL;
	game->instance = NULL;
	game->game_state = GAME_STATE_MAIN_MENU;
	game->camera = NULL;
	game->input = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "Couldn't initialize SDL, SDL_Error: %s\n", SDL_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}

	if (TTF_Init()) {
		fprintf(stderr, "Couldn't initialize TTF, TTF_Error: %s\n", TTF_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}

	if (!((IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS) == IMG_INIT_FLAGS)) {
		fprintf(stderr, "Couldn't initialize IMG, IMG_Error: %s\n", IMG_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}

	game->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (game->window == NULL) {
		fprintf(stderr, "Couldn't create window, SDL_Error: %s\n", SDL_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}
	
	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (game->renderer == NULL) {
		fprintf(stderr, "Couldn't create renderer, SDL_Error: %s\n", SDL_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}


	game->camera = initialize_camera();
	if (game->camera == NULL) {
		fprintf(stderr, "Couldn't create camera\n");
		cleanup_game(game, EXIT_FAILURE);
	}

	game->input = initialize_input();
	if (game->input == NULL) {
		fprintf(stderr, "Couldn't initialize input\n");
		cleanup_game(game, EXIT_FAILURE);
	}
};

void handle_event(Game *game, SDL_Event *event) {
	switch (event->type) {
		case SDL_QUIT:
			cleanup_game(game, EXIT_SUCCESS);
			break;
		case SDL_KEYDOWN:
			press_button(game->input, event->key.keysym.scancode);
			break;
		case SDL_KEYUP:
			unpress_button(game->input, event->key.keysym.scancode);
			break;
	}
}

void run_game(Game *game) {

	game->instance = load_instance(1);
	if (game->instance == NULL) {
		fprintf(stderr, "Couldn't load instance\n");
		cleanup_game(game, EXIT_FAILURE);
	}

	if (game->instance->start_section == NULL) {
		fprintf(stderr, "Couldn't load start section\n");
		cleanup_game(game, EXIT_FAILURE);
	}

	Character *character = initialize_character();
	if (character == NULL) {
		fprintf(stderr, "Couldn't initialize character\n");
		cleanup_game(game, EXIT_FAILURE);
	}

	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event))
			handle_event(game, &event);

		update_camera_state(game->input, game->camera);

		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(game->renderer);

		calculate_character_speed(game, character);
		calculate_character_position(game, character);

		render_section(game, game->instance->start_section);
		render_unit(game, &character->unit);

		SDL_RenderPresent(game->renderer);

		SDL_Delay(DEFAULT_RENDER_DELAY);
	}
}
