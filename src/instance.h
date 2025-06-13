#ifndef INSTANCE_H
#define INSTANCE_H

typedef struct Block Block;

typedef struct Section {
	float w, h;

	Block *blocks;
	int blocks_len;

	struct Section *left;
	struct Section *right;
	struct Section *up;
	struct Section *down;
} Section;

typedef enum {
	ENTRY_LEFT,
	ENTRY_RIGHT,
	ENTRY_TOP,
	ENTRY_BOTTOM,
} Entry;

typedef struct Instance {
	Section *start_section;
	Section *current_section;
	Entry entry;
} Instance;

Instance *load_instance(int instance_id);
void print_instance(Instance *instance);
void print_section(Section *section);
void unload_instance(Instance *instance);

#endif // INSTANCE_H
