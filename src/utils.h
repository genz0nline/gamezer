#ifndef UTILS_H
#define UTILS_H

typedef struct {
	float x, y;
} Coordinate;

float distance(Coordinate a, Coordinate b);
char* read_file(const char* filename);

#endif // UTILS_H
