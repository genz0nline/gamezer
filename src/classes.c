#include "classes.h"
#include "utils.h"
#include <assert.h>
#include <json.h>
#include <stdio.h>
#include <stdlib.h>

const char *ID_NAME_KEY = "id";
const char *NAME_KEY = "name";
const char *SPRITE_ID_KEY = "sprite_id";

CharacterClass *load_character_class(int class_id) {
	CharacterClass *character_class = (CharacterClass *)malloc(sizeof(CharacterClass));

	char file_name[MAX_CLASS_FILE_NAME_LEN];
	sprintf(file_name, "src/static/classes/%d.json", class_id);

	char *class_json = read_file(file_name);

	struct json_value_s *root = json_parse(class_json, strlen(class_json));

	assert(root->type == json_type_object);
	struct json_object_s *obj = (struct json_object_s *)root->payload;

	struct json_object_element_s *element = obj->start;
	while (element != NULL) {
		if (strncmp(NAME_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			strncpy(character_class->name, json_value_as_string(element->value)->string, MAX_CLASS_NAME_LEN);
		}

		if (strncmp(ID_NAME_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			character_class->id = atoi(json_value_as_number(element->value)->number);
		}

		if (strncmp(SPRITE_ID_KEY, element->name->string, element->name->string_size) == 0) {
			assert(element->value->type == json_type_number);
			character_class->sprite_id = atoi(json_value_as_number(element->value)->number);
		}

		element = element->next;
	}

	free(root);

	return character_class;
}


void unload_character_class(CharacterClass *character_class) {
	if (character_class == NULL)
		return;

	free(character_class);
}
