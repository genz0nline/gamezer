#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "game.h"

const char *title = "Gamezer";
const int IMG_INIT_FLAGS = IMG_INIT_PNG;

void cleanup_game(Game *game, int error_code) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error_code);
}

void initialize_game(Game *game) {

	game->w = DEFAULT_SCREEN_WIDTH;
	game->h = DEFAULT_SCREEN_HEIGHT;
	game->window = NULL;
	game->renderer = NULL;
	game->instance = NULL;
	game->game_state = GAME_STATE_MAIN_MENU;

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

	game->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	if (game->window == NULL) {
		fprintf(stderr, "Couldn't create window, SDL_Error: %s\n", SDL_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}
	
	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (game->renderer == NULL) {
		fprintf(stderr, "Couldn't create renderer, SDL_Error: %s\n", SDL_GetError());
		cleanup_game(game, EXIT_FAILURE);
	}
};
