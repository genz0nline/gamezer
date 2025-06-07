#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "instance.h"

#define DEFAULT_SCREEN_WIDTH		1920
#define DEFAULT_SCREEN_HEIGHT		1080

typedef enum {
	GAME_STATE_MAIN_MENU,
	GAME_STATE_INSTANCE,
	GAME_STATE_PAUSED,
} GameState;

typedef struct Game {
	int w, h;
	SDL_Window *window;
	SDL_Renderer *renderer;
	GameState game_state;
	Instance *instance;
} Game;

void cleanup_game(Game *game, int error_code);
void initialize_game(Game *game);

#endif // GAME_H
