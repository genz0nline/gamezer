#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

const float DEFAULT_CAPTURE_WINDOW_WIDTH = 20;
const float MIN_ZOOM_FACTOR = .1;
const float MAX_ZOOM_FACTOR = 10;

typedef struct Camera {
	Coordinate position;
	float zoom_factor;
} Camera;

#endif // CAMERA_H
