#ifndef UTILS_H
#define UTILS_H

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct Coordinate {
	float x, y;
} Coordinate;

typedef struct ScreenCoordinate {
	int x, y;
} ScreenCoordinate;

typedef struct Dimensions {
	float w, h;
} Dimensions;

typedef struct ScreenDimensions {
	int w, h;
} ScreenDimensions;

float distance(Coordinate a, Coordinate b);
char* read_file(const char* filename);

#endif // UTILS_H
