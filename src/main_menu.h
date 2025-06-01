#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game.h"

extern char *main_menu_options[];
extern int main_menu_options_len;
extern int highlighted_option_index;

void render_main_menu(Game *game);
void choose_main_menu_option(Game *game);

#endif // MAIN_MENU_H
