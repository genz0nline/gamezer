#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

extern bool left_pressed;
extern bool right_pressed;
extern bool up_pressed;
extern bool up_just_pressed;
extern bool down_pressed;

void initialize_input();
void handle_keydown(SDL_Keycode sym);
void handle_keyup(SDL_Keycode sym);

#endif
