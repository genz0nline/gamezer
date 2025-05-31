#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "character.h"
#include "environment.h"
#include "camera.h"
#include "input.h"
#include "main_menu.h"

const char *GAME_TITLE = "Gamezer";
int screen_width = 1920;
int screen_height = 1080;

Game initialize_game(void) {
	Game game = {
		.window = NULL,
		.renderer = NULL,
		.lvl = NULL,
		.game_state = MAIN_MENU,
	};


	return game;
}

bool game_cleanup(Game *game, int exit_code) {
	free_level(game->lvl);
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

	game->window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_FULLSCREEN);
	if (!game->window) {
		fprintf(stderr, "SDL couldn't create window, SDL_ERROR: %s\n", SDL_GetError());
		return true;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (!game->renderer) {
		fprintf(stderr, "SDL couldn't create renderer, SDL_ERROR: %s\n", SDL_GetError());
		return true;
	}

	if (TTF_Init()) {
		fprintf(stderr, "TTF couldn't initialize, TTF_Error: %s\n", TTF_GetError());
		return true;
	}

	return false;
}

void update_game_state(Game *game) {
	update_environment_state(game->lvl);
	update_character_state(game->lvl);
	update_camera_position(game->lvl);
}

void render_background(SDL_Renderer *renderer, Level *lvl) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void render_environment(SDL_Renderer *renderer, Level *lvl) {
	render_background(renderer, lvl);
	draw_default_level(renderer, lvl);
}

void render_character(SDL_Renderer *renderer, Level *lvl) {
	draw_character(renderer, lvl);
}

void render_frame(Game *game) {
	render_environment(game->renderer, game->lvl);
	render_character(game->renderer, game->lvl);

	SDL_RenderPresent(game->renderer);
}

void restart_game(Level **lvl) {
	free_level(*lvl);
	*lvl = initialize_default_level();
	spawn_character(*lvl);
}

int start_game(void) {
	Game game = initialize_game();
	if(initialize_sdl(&game)) {
		game_cleanup(&game, EXIT_FAILURE);
	}

	SDL_Event e;

	printf("Game has started...\n");

	while (true) {
		switch (game.game_state) {
			case MAIN_MENU:
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						game_cleanup(&game, EXIT_SUCCESS);
					} else if (e.type == SDL_KEYDOWN) {
						handle_main_menu_keydown(e.key.keysym.sym, &game);
					}
				}
				render_main_menu(&game);
				break;
			case IN_PLAY:
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						game_cleanup(&game, EXIT_SUCCESS);
					} else if (e.type == SDL_KEYDOWN) {
						handle_in_play_keydown(e.key.keysym.sym, &game);
					} else if (e.type == SDL_KEYUP) {
						handle_in_play_keyup(e.key.keysym.sym);
					}
				}
				update_game_state(&game);
				render_frame(&game);
				break;
		}


		SDL_Delay(10);
	}
}
