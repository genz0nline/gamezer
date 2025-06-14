#ifndef COORDINATE_TRANSFORMATION_H
#define COORDINATE_TRANSFORMATION_H

#include <SDL2/SDL.h>

typedef struct ScreenCoordinate ScreenCoordinate;
typedef struct ScreenDimensions ScreenDimensions;
typedef struct Game Game;
typedef struct Dimensions Dimensions;
typedef struct Coordinate Coordinate;

ScreenCoordinate get_screen_coordinate(Game *game, Coordinate game_coordinate);
ScreenDimensions get_screen_dimensions(Game *game, Dimensions game_dimentions);
SDL_Rect get_rectangle(Game *game, float x_m, float y_m, float w_m, float h_m);


#endif // COORDINATE_TRANSFORMATION_H
