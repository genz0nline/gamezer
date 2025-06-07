#include "game.h"

int main(void) {
	Game game;
	initialize_game(&game);
	cleanup_game(&game, EXIT_SUCCESS);
	return 0;
}
