#include <stdlib.h>

#include "classes.h"
#include "skills.h"

Skill *initialize_warrior_skills(void) {
	Skill *skills = (Skill *)malloc(NUMBER_OF_SKILLS * sizeof(Skill));
	initialize_skill_vicious_slash(skills);

	return skills;
}
