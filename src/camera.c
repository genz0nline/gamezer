#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdlib.h>
#include "camera.h"
#include "utils.h"
#include "input.h"

Camera *initialize_camera(void) {
	Camera *camera = (Camera *)malloc(sizeof(Camera));

	camera->position.x = 20;
	camera->position.y = 15;
	camera->zoom_factor = DEFAULT_ZOOM_FACTOR;
	camera->last_update_tick = SDL_GetTicks();
	camera->zoom_speed = .1;

	return camera;
}

void free_camera(Camera *camera) {
	if (camera == NULL)
		return;
	free(camera);
}

void update_camera_state(Input *input, Camera *camera) {
	Uint32 tick = SDL_GetTicks();

	int milliseconds = tick - camera->last_update_tick;

	if (input->minus_pressed) {
		camera->zoom_factor += camera->zoom_speed * milliseconds / 1000;
		camera->zoom_factor = MIN(MAX_ZOOM_FACTOR, camera->zoom_factor);
		printf("New zoom_factor = %f\n", camera->zoom_factor);
	} else if (input->equals_pressed) {
		camera->zoom_factor -= camera->zoom_speed * milliseconds / 1000;
		camera->zoom_factor = MAX(MIN_ZOOM_FACTOR, camera->zoom_factor);
		printf("New zoom_factor = %f\n", camera->zoom_factor);
	}
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
