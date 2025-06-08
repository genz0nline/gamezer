#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "instance.h"
#include "camera.h"

#define DEFAULT_SCREEN_WIDTH		1200
#define DEFAULT_SCREEN_HEIGHT		900
#define DEFAULT_RENDER_DELAY		10

typedef enum {
	GAME_STATE_MAIN_MENU,
	GAME_STATE_INSTANCE,
	GAME_STATE_PAUSED,
} GameState;

typedef struct Game {
	int screen_width, screen_height;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Camera *camera;
	GameState game_state;
	Instance *instance;
} Game;

void cleanup_game(Game *game, int error_code);
void initialize_game(Game *game);
void run_game(Game *game);

#endif // GAME_H
