#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "utils.h"

#define CAPTURE_WINDOW_WIDTH_PER_ZF			2
#define DEFAULT_ZOOM_FACTOR					20
#define MIN_ZOOM_FACTOR						1
#define MAX_ZOOM_FACTOR						100

typedef struct Game Game;

typedef struct Camera {
	Coordinate position;
	float zoom_factor;
	float zoom_speed;
	Uint32 last_update_tick;
} Camera;

Camera *initialize_camera(void);
void free_camera(Camera *camera);

void update_camera_state(Game *game, Camera *camera);

void zoom_in(Camera *camera);
void zoom_out(Camera *camera);

#endif // CAMERA_H
