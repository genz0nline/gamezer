#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "environment.h"

extern const char *GAME_TITLE;
extern int screen_width;
extern int screen_height;

#define UPDATE_TICK_RATE	15

typedef struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Game;

int start_game(void);

Game initialize_game(void);
bool game_cleanup(Game *game, int exit_code);
void restart(Level **lvl);

#endif
