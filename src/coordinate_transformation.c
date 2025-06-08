#include "coordinate_transformation.h"

#include "camera.h"
#include "game.h"
#include "utils.h"
#include <SDL2/SDL_rect.h>

ScreenCoordinate get_screen_coordinate(Game *game, Coordinate game_coordinate) {

	float capture_window_height_per_zf = (float) CAPTURE_WINDOW_WIDTH_PER_ZF * game->screen_height / game->screen_width;

	return (ScreenCoordinate) {
		.x = (int) (game->screen_width * (.5 + ( game_coordinate.x - game->camera->position.x ) / ( game->camera->zoom_factor * CAPTURE_WINDOW_WIDTH_PER_ZF ))),
		.y = (int) (game->screen_height * (.5 + ( game->camera->position.y - game_coordinate.y ) / ( game->camera->zoom_factor * capture_window_height_per_zf ))),
	};
}

ScreenDimensions get_screen_dimensions(Game *game, Dimensions game_dimentions) {

	float capture_window_height_per_zf = (float) CAPTURE_WINDOW_WIDTH_PER_ZF * game->screen_height / game->screen_width;

	return (ScreenDimensions) {
		.w = (int) ((game->screen_width * game_dimentions.w) / (game->camera->zoom_factor * CAPTURE_WINDOW_WIDTH_PER_ZF)),
		.h = (int) ((game->screen_height * game_dimentions.h) / (game->camera->zoom_factor * capture_window_height_per_zf)),
	};
}

SDL_Rect get_rectangle(Game *game, float x_m, float y_m, float w_m, float h_m) {

	ScreenCoordinate screen_coordinate = get_screen_coordinate(game, (Coordinate) {.x = x_m, .y = y_m});
	ScreenDimensions screen_dimensions = get_screen_dimensions(game, (Dimensions) {.w = w_m, .h = h_m});

	SDL_Rect rect = {
		.x = screen_coordinate.x,
		.y = screen_coordinate.y - screen_dimensions.h,
		.w = screen_dimensions.w,
		.h = screen_dimensions.h,
	};

	return rect;
}
