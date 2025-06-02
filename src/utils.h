#ifndef UTILS_H
#define UTILS_H

#define MAX(A, B)		(A) > (B) ? (A) : (B)
#define MIN(A, B)		(A) < (B) ? (A) : (B)
#define ABS(A)			((A) < 0 ? -(A) : (A))

typedef struct {
	float x_m, y_m;
} Coordinate;

float distance(Coordinate a, Coordinate b);

#endif
