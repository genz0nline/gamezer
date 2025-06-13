#ifndef CLASSES_H
#define CLASSES_H

#define MAX_CLASS_NAME_LEN		20
#define MAX_CLASS_FILE_NAME_LEN			100

typedef struct CharacterClass {
	int id;
	char name[MAX_CLASS_NAME_LEN];
	int sprite_id;
} CharacterClass;

CharacterClass *load_character_class(int class_id);
void unload_character_class(CharacterClass *character_class);

#endif // CLASSES_H
