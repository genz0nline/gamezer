#include "utils.h"
#include <math.h>

float distance(Coordinate a, Coordinate b) {
	float square = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	return pow(square, .5);
}
