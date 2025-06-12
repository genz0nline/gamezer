#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <json.h>
#include <string.h>

#include "instance.h"
#include "utils.h"

const char *W_KEY = "w";
const char *H_KEY = "h";
const char *X_KEY = "x";
const char *Y_KEY = "y";
const char *BLOCKS_KEY = "blocks";
const char *RIGHT_KEY = "right";
const char *LEFT_KEY = "left";
const char *UP_KEY = "up";
const char *DOWN_KEY = "down";

void load_block(struct json_value_s *value, Block *block) {
	assert(value->type == json_type_object);

	struct json_object_s *obj = (struct json_object_s *)value->payload;

	struct json_object_element_s *element = obj->start;
	while (element != NULL) {
		if (strncmp(W_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			block->w = atof(json_value_as_number(element->value)->number);
		}

		if (strncmp(H_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			block->h = atof(json_value_as_number(element->value)->number);
		}

		if (strncmp(X_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			block->x = atof(json_value_as_number(element->value)->number);
		}

		if (strncmp(Y_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			block->y = atof(json_value_as_number(element->value)->number);
		}

		element = element->next;
	}
}

void load_blocks(Section *section, struct json_value_s *value) {
	assert(value->type == json_type_array);

	section->blocks_len = 0;
	struct json_array_element_s *p = ((struct json_array_s *)value->payload)->start;

	while (p != NULL) {
		section->blocks_len++;
		p = p->next;
	}

	Block *blocks_p = (Block *)malloc(section->blocks_len * sizeof(Block));
	section->blocks = blocks_p;

	p = ((struct json_array_s *)value->payload)->start;
	while (p != NULL) {
		load_block(p->value, blocks_p);
		p = p->next;
		blocks_p++;
	}
}

Section *load_section(struct json_value_s *node) {
	if (node->type == json_type_null)
		return NULL;

	assert(node->type == json_type_object);

	Section *section = (Section *)malloc(sizeof(Section));

	struct json_object_s *obj = (struct json_object_s *)node->payload;

	struct json_object_element_s *element = obj->start;
	while (element != NULL) {
		if (strncmp(W_KEY, element->name->string, element->name->string_size) == 0) {
			printf("I am here\n");
			assert(element->value->type == json_type_number);
			section->w = atof(json_value_as_number(element->value)->number);
		}

		if (strncmp(H_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			section->h = atof(json_value_as_number(element->value)->number);
		}

		if (strncmp(BLOCKS_KEY, element->name->string, element->name->string_size) == 0) {
			load_blocks(section, element->value);
		}

		if (strncmp(RIGHT_KEY, element->name->string, element->name->string_size) == 0) {
			section->right=load_section(element->value);
		}

		if (strncmp(LEFT_KEY, element->name->string, element->name->string_size) == 0) {
			section->left=load_section(element->value);
		}

		if (strncmp(UP_KEY, element->name->string, element->name->string_size) == 0) {
			section->up=load_section(element->value);
		}

		if (strncmp(DOWN_KEY, element->name->string, element->name->string_size) == 0) {
			section->down=load_section(element->value);
		}

		element = element->next;
	}

	return section;
}

Instance *load_instance(int instance_id) {
	char file_name[100];
	sprintf(file_name, "src/static/instances/%d.json", instance_id);

	Instance *instance = (Instance *)malloc(sizeof(Instance));

	char *instance_json = read_file(file_name);

	struct json_value_s *root = json_parse(instance_json, strlen(instance_json));
	instance->start_section = load_section(root);
	instance->current_section = instance->start_section;
	instance->entry = ENTRY_LEFT;

	free(root);

	return instance;
}

void print_blocks(Section *section) {
	for (int i = 0; i < section->blocks_len; i++) {
		printf("\t(%f, %f, %f, %f)\n", (section->blocks + i)->w, (section->blocks + i)->h, (section->blocks + i)->x, (section->blocks + i)->y); 
	}
}


void print_section(Section *section) {
	if (section == NULL)
		return;

	printf("w, h = %f, %f\n", section->w, section->h);
	print_blocks(section);
	print_section(section->right);
	print_section(section->left);
	print_section(section->up);
	print_section(section->down);
}

void print_instance(Instance *instance) {
	printf("============\n");
	if (instance == NULL)
		return;

	print_section(instance->start_section);

	printf("============\n");
}

void unload_section(Section *section) {
	if (section == NULL)
		return;

	unload_section(section->right);
	unload_section(section->left);
	unload_section(section->up);
	unload_section(section->down);

	if (section->blocks != NULL)
		free(section->blocks);
	free(section);
}

void unload_instance(Instance *instance) {

	if (instance == NULL)
		return;

	unload_section(instance->start_section);

	free(instance);
}
