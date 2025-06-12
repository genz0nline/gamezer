#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
	bool left_pressed;
	bool right_pressed;
	bool up_pressed;
	bool down_pressed;
	bool minus_pressed;
	bool equals_pressed;
} Input;

Input *initialize_input(void);
void cleanup_input(Input *input);
void press_button(Input *input, SDL_Scancode scancode);
void unpress_button(Input *input, SDL_Scancode scancode);

#endif // INPUT_H
