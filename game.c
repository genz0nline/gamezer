#include "game.h"
#include "character.h"
#include "environment.h"
#include "camera.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const char *GAME_TITLE = "Gamezer";
int screen_width = 900;
int screen_height = 600;


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

	window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL couldn't create window, SDL_ERROR: %s\n", SDL_GetError());
	}

	screen_surface = SDL_GetWindowSurface(window);
	if (screen_surface == NULL) {
		fprintf(stderr, "SDL couldn't create screen surface, SDL_ERROR: %s\n", SDL_GetError());
	}

	SDL_Rect screen_surface_rect = {0, 0, screen_width, screen_height};
	SDL_FillRect(screen_surface, &screen_surface_rect, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);

	Level *lvl = initialize_default_level();
	spawn_character(lvl);
	initialize_camera(lvl);

	SDL_Event e;

	bool right_pressed;
	bool left_pressed;
	bool up_pressed;
	bool down_pressed;

	printf("Game has started...\n");
	bool quit = false;
	while (!quit) {

		right_pressed = false;
		left_pressed = false;
		up_pressed = false;
		down_pressed = false;

		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			quit = true;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					right_pressed = true;
					break;
				case SDLK_LEFT:
					left_pressed = true;
					break;
				case SDLK_UP:
					up_pressed = true;
					break;
				case SDLK_DOWN:
					down_pressed = true;
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

		if (right_pressed) {
			if (character.x_m <= lvl->width_m - character.w_m - 1)
				character.x_m += 1;
			else
				character.x_m = lvl->width_m - character.w_m;
		}
		if (left_pressed) {
			if (character.x_m >= 1)
				character.x_m -= 1;
			else 
				character.x_m = 0;
		}
		if (up_pressed) {
			if (character.y_m <= lvl->height_m - 1)
				character.y_m += 1;
			else 
				character.y_m = lvl->height_m;
		}
		if (down_pressed) {
			if (character.y_m >= character.h_m + 1)
				character.y_m -= 1;
			else
				character.y_m = character.h_m;
		}
		center_camera(lvl);

		// printf("Camera position: (%f, %f)\n", camera_center_pos_x_m, camera_center_pos_y_m);
		SDL_FillRect(screen_surface, &screen_surface_rect, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
		draw_default_level(lvl, screen_surface);
		draw_character(lvl, screen_surface);
		SDL_UpdateWindowSurface(window);
	}

	free_level(lvl);

	printf("Game has ended...\n");
	return 0;
}
