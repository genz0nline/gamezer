#include "game.h"
#include "environment.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const char *GAME_TITLE = "Gamezer";
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;


enum GAME_STATE {
	GAME_STATE_MAIN_MENU,
	GAME_STATE_IN_PLAY,
	GAME_STATE_PAUSED,
};


int start_game(void) {

	SDL_Window *window = NULL;
	SDL_Surface *screen_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO & SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL couldn't initialize, SDL_ERROR: %s\n", SDL_GetError());
	}

	window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL couldn't create window, SDL_ERROR: %s\n", SDL_GetError());
	}

	screen_surface = SDL_GetWindowSurface(window);
	if (screen_surface == NULL) {
		fprintf(stderr, "SDL couldn't create screen surface, SDL_ERROR: %s\n", SDL_GetError());
	}

	SDL_Rect screen_surface_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_FillRect(screen_surface, &screen_surface_rect, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);

	Level *lvl = initialize_default_level();

	SDL_Event e;

	printf("Game has started...\n");
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		SDL_FillRect(screen_surface, &screen_surface_rect, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
		draw_default_level(lvl, screen_surface);
		SDL_UpdateWindowSurface(window);
	}

	free_level(lvl);

	printf("Game has ended...\n");
	return 0;
}
