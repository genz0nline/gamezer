#ifndef GAME_RECT_H
#define GAME_RECT_H

#include <stdbool.h>

typedef struct {
	float x, y;
	float w, h;
} GameRect;

bool check_collision(GameRect a, GameRect b);

#endif // GAME_RECT_H
