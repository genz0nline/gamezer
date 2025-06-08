#include <stdbool.h>
#include "game_rect.h"

bool check_collision(GameRect a, GameRect b) {
	if (a.x + a.w < b.x)
		return false;

	if (a.y + a.h < b.y)
		return false;

	if (b.x + b.w < a.x)
		return false;

	if (b.y + b.h < a.y)
		return false;

	return true;
}
