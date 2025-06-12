#ifndef UTILS_H
#define UTILS_H

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	float x, y;
} Coordinate;

typedef struct {
	int x, y;
} ScreenCoordinate;

typedef struct {
	float w, h;
} Dimensions;

typedef struct {
	int w, h;
} ScreenDimensions;

float distance(Coordinate a, Coordinate b);
char* read_file(const char* filename);

#endif // UTILS_H
