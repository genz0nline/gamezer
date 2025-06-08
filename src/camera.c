#include <SDL2/SDL.h>
#include <stdlib.h>
#include "camera.h"
#include "utils.h"

Camera *initialize_camera(void) {
	Camera *camera = (Camera *)malloc(sizeof(Camera));

	camera->position.x = 20;
	camera->position.y = 15;
	camera->zoom_factor = DEFAULT_ZOOM_FACTOR;

	return camera;
}

void free_camera(Camera *camera) {
	if (camera == NULL)
		return;
	free(camera);
}

void zoom_in(Camera *camera) {
	camera->zoom_factor -= 1;
	camera->zoom_factor = MAX(MIN_ZOOM_FACTOR, camera->zoom_factor);
	printf("New zoom_factor = %d\n", camera->zoom_factor);
}

void zoom_out(Camera *camera) {
	camera->zoom_factor += 1;
	camera->zoom_factor = MIN(MAX_ZOOM_FACTOR, camera->zoom_factor);
	printf("New zoom_factor = %d\n", camera->zoom_factor);
}
