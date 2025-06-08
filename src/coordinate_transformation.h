#ifndef COORDINATE_TRANSFORMATION_H
#define COORDINATE_TRANSFORMATION_H

#include "utils.h"
#include "game.h"
#include "camera.h"

ScreenCoordinate get_screen_coordinate(Game *game, Coordinate game_coordinate);
ScreenDimensions get_screen_dimensions(Game *game, Dimensions game_dimentions);
SDL_Rect get_rectangle(Game *game, float x_m, float y_m, float w_m, float h_m);


#endif // COORDINATE_TRANSFORMATION_H
