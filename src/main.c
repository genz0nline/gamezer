#include <SDL2/SDL.h>
#include <stdbool.h>

#include "game.h"

int main(void) {
	Game game;
	initialize_game(&game);

	run_game(&game);

	cleanup_game(&game, EXIT_SUCCESS);
}
