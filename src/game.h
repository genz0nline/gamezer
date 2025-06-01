#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "environment.h"

extern const char *GAME_TITLE;
extern int screen_width;
extern int screen_height;

#define UPDATE_TICK_RATE	15
#define GRAVITY_FORCE		98

enum GAME_STATE {
	MAIN_MENU,
	IN_PLAY,
	PAUSED,
	GAME_OVER,
};

typedef struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Level *lvl;
	int game_state;
} Game;

int start_game();

Game initialize_game(void);
bool game_cleanup(Game *game, int exit_code);
void restart_game(Level **lvl);

#endif
