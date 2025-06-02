#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "main_menu.h"
#include "camera.h"
#include "character.h"
#include "classes.h"
#include "game.h"
#include "input.h"

#define MAIN_MENU_OPTIONS_GAP			10
#define MAIN_MENU_RELATIVE_WIDHT		.4
#define MAIN_MENU_RELATIVE_HEIGHT		.6

enum MAIN_MENU_OPTIONS {
	START_GAME = 0,
	SETTINGS = 1,
	CREATORS = 2,
	EXIT_GAME = 3,
};

char *START_GAME_TEXT  = "Start game";
char *SETTINGS_TEXT  = "Settings";
char *CREATORS_TEXT  = "Creators";
char *EXIT_GAME_TEXT  = "Exit game";

int main_menu_options_len = 4;
int highlighted_option_index = 0;

int menu_width;
int menu_height;
int menu_option_height;
int menu_x;
int menu_y;

SDL_Rect get_main_menu_option_rect(int index) {
	int y = menu_y + index * (menu_option_height + MAIN_MENU_OPTIONS_GAP);
	SDL_Rect rect = {menu_x, y, menu_width, menu_option_height};
	return rect;
}

void draw_main_menu_option(SDL_Renderer *renderer, int index) {
	SDL_Rect rect = get_main_menu_option_rect(index);
	if (index == highlighted_option_index)
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xDF, 0x00, SDL_ALPHA_OPAQUE);
	else
		SDL_SetRenderDrawColor(renderer, 0xD4, 0xAF, 0x37, SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer, &rect);

	char *text;
	switch (index) {
		case 0:
			text=START_GAME_TEXT;
			break;
		case 1:
			text=SETTINGS_TEXT;
			break;
		case 2:
			text=CREATORS_TEXT;
			break;
		case 3:
			text=EXIT_GAME_TEXT;
			break;
	}

	SDL_Color color = {0, 0, 0};

	TTF_Font *font = TTF_OpenFont("src/static/fonts/Montserrat-SemiBold.ttf", 65);

	if (font == NULL) {
		printf("%s\n", TTF_GetError());
	}

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
	if (textSurface == NULL) {
		exit(123);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;
	textRect.x = (int) rect.x + (rect.w - textRect.w) / 2;
	textRect.y = (int) rect.y + (rect.h - textRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void render_main_menu(Game *game) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(game->renderer);

	menu_width = (int) (screen_width * MAIN_MENU_RELATIVE_WIDHT); 
	menu_height = (int) (screen_height * MAIN_MENU_RELATIVE_HEIGHT); 
	menu_option_height = (int) ((menu_height - (main_menu_options_len - 1) * MAIN_MENU_OPTIONS_GAP) / main_menu_options_len);
	menu_x = (int) ((screen_width - menu_width) / 2);
	menu_y = (int) ((screen_height - menu_height) / 2);

	for (int i = 0; i < main_menu_options_len; i++) {
		draw_main_menu_option(game->renderer, i);
	}

	SDL_RenderPresent(game->renderer);
}

void choose_main_menu_option(Game *game) {
	switch (highlighted_option_index) {
		case START_GAME:
			game->lvl = initialize_default_level();
			spawn_character(game->lvl, WARRIOR);
			initialize_camera(game->lvl);
			initialize_input();
			game->game_state=IN_PLAY;
			break;
		case EXIT_GAME:
			game_cleanup(game, EXIT_SUCCESS);
	}
}
