#ifndef CLASSES_H
#define CLASSES_H

#include "skills.h"

#define NUMBER_OF_SKILLS	1


#define Character_Class	int
enum CLASSES_ENUM {
	WARRIOR,
	RANGER,
	MAGE,
};

Skill *initialize_warrior_skills(void);

#endif // CLASSES_H
