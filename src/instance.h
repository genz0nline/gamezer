#ifndef INSTANCE_H
#define INSTANCE_H

#include "blocks.h"

typedef struct Section {
	float w, h;

	Block *blocks;
	int blocks_len;

	struct Section *left;
	struct Section *right;
	struct Section *up;
	struct Section *down;
} Section;

typedef struct Instance {
	Section *start_section;
} Instance;

#endif // INSTANCE_H
