#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_stdinc.h>
#include <stdlib.h>
#include "instance.h"
#include "camera.h"
#include "utils.h"
#include "units.h"
#include "input.h"
#include "game.h"

Camera *initialize_camera(void) {
	Camera *camera = (Camera *)malloc(sizeof(Camera));

	camera->position.x = 20;
	camera->position.y = 15;
	camera->zoom_factor = DEFAULT_ZOOM_FACTOR;
	camera->last_update_tick = SDL_GetTicks();
	camera->zoom_speed = 3;

	return camera;
}

void free_camera(Camera *camera) {
	if (camera == NULL)
		return;
	free(camera);
}

void update_camera_state(Game *game, Camera *camera) {
	Uint32 tick = SDL_GetTicks();

	int milliseconds = tick - camera->last_update_tick;

	if (game->input->minus_pressed) {
		camera->zoom_factor += camera->zoom_speed * milliseconds / 1000;
		camera->zoom_factor = MIN(MAX_ZOOM_FACTOR, camera->zoom_factor);
		printf("New zoom_factor = %f\n", camera->zoom_factor);
	} else if (game->input->equals_pressed) {
		camera->zoom_factor -= camera->zoom_speed * milliseconds / 1000;
		camera->zoom_factor = MAX(MIN_ZOOM_FACTOR, camera->zoom_factor);
		printf("New zoom_factor = %f\n", camera->zoom_factor);
	}

	camera->position.x = game->character->unit.x;
	camera->position.y = game->character->unit.y;

	float width = camera->zoom_factor * CAPTURE_WINDOW_WIDTH_PER_ZF;
	float height = width * game->screen_height / game->screen_width;
	camera->position.x = MAX(camera->position.x, width * .5);
	camera->position.x = MIN(camera->position.x, game->instance->current_section->w - width * .5);
	camera->position.y = MAX(camera->position.y, height * .5);
	camera->position.y = MIN(camera->position.y, game->instance->current_section->h - height * .5);

	camera->last_update_tick = tick;
	
}

void zoom_in(Camera *camera) {
	camera->zoom_factor -= 1;
	camera->zoom_factor = MAX(MIN_ZOOM_FACTOR, camera->zoom_factor);
	printf("New zoom_factor = %f\n", camera->zoom_factor);
}

void zoom_out(Camera *camera) {
	camera->zoom_factor += 1;
	camera->zoom_factor = MIN(MAX_ZOOM_FACTOR, camera->zoom_factor);
	printf("New zoom_factor = %f\n", camera->zoom_factor);
}
