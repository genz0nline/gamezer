#ifndef UTILS_H
#define UTILS_H

#define MAX(A,B)		(A) > (B) ? (A) : (B)
#define MIN(A,B)		(A) < (B) ? (A) : (B)

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
