#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "character.h"
#include "environment.h"
#include "camera.h"
#include "input.h"

const char *GAME_TITLE = "Gamezer";
int screen_width = 1200;
int screen_height = 675;

Game initialize_game(void) {
	Game game = {
		.window = NULL,
		.renderer = NULL,
	};

	return game;
}

bool game_cleanup(Game *game, int exit_code) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();

	printf("Game has ended!\n");
	exit(exit_code);
}

bool initialize_sdl(Game *game) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL couldn't initialize, SDL_ERROR: %s\n", SDL_GetError());
		return true;
	}

	game->window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (!game->window) {
		fprintf(stderr, "SDL couldn't create window, SDL_ERROR: %s\n", SDL_GetError());
		return true;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (!game->renderer) {
		fprintf(stderr, "SDL couldn't create renderer, SDL_ERROR: %s\n", SDL_GetError());
		return true;
	}

	return false;
}

void update_game_state(Level *lvl) {
	update_level_state(lvl);
	update_character_state(lvl);
	update_camera_position(lvl);
}

void render_frame(Game *game, Level *lvl) {
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(game->renderer);
	draw_default_level(lvl, game->renderer);
	draw_character(lvl, game->renderer);
	SDL_RenderPresent(game->renderer);
}

void restart(Level **lvl) {
	free_level(*lvl);
	*lvl = initialize_default_level();
	spawn_character(*lvl);
}

int start_game(void) {
	Game game = initialize_game();
	if(initialize_sdl(&game)) {
		game_cleanup(&game, EXIT_FAILURE);
	}

	Level *lvl = initialize_default_level();
	spawn_character(lvl);
	initialize_camera(lvl);
	initialize_input();

	SDL_Event e;

	printf("Game has started...\n");

	while (true) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			free_level(lvl);
			game_cleanup(&game, EXIT_SUCCESS);
		} else if (e.type == SDL_KEYDOWN) {
			handle_keydown(e.key.keysym.sym, &lvl);
		} else if (e.type == SDL_KEYUP) {
			handle_keyup(e.key.keysym.sym);
		}

		update_game_state(lvl);
		render_frame(&game, lvl);

		SDL_Delay(10);
	}
}
