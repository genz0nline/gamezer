#include "utils.h"
#include <math.h>

float distance(Coordinate a, Coordinate b) {
	float square_dist = pow(a.x_m - b.x_m, 2) + pow(a.y_m - b.y_m, 2);

	return pow(square_dist, .5);
}

