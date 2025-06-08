#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include <SDL2/SDL.h>

#define CAPTURE_WINDOW_WIDTH_PER_ZF			2
#define DEFAULT_ZOOM_FACTOR					100
#define MIN_ZOOM_FACTOR						1
#define MAX_ZOOM_FACTOR						100

typedef struct {
	Coordinate position;
	int zoom_factor;
} Camera;

Camera *initialize_camera(void);
void free_camera(Camera *camera);
void zoom_in(Camera *camera);
void zoom_out(Camera *camera);


#endif // CAMERA_H
