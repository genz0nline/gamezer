#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#define DEFAULT_SCREEN_WIDTH		1920
#define DEFAULT_SCREEN_HEIGHT		1080
#define DEFAULT_RENDER_DELAY		10

typedef struct Camera Camera;
typedef struct Instance Instance;
typedef struct Input Input;
typedef struct Character Character;

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
	Input *input;
	Character *character;
} Game;

void cleanup_game(Game *game, int error_code);
void initialize_game(Game *game);
void run_game(Game *game);

#endif // GAME_H
