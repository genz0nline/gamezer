#include "game.h"
#include "instance.h"

int main(void) {
	Game game;
	initialize_game(&game);

	Instance *instance = load_instance(1);
	print_instance(instance);

	cleanup_game(&game, EXIT_SUCCESS);
	return 0;
}
