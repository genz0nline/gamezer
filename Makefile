CC = gcc
CFLAGS = -Wall -g `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

SRC = src/main.c src/game.c src/environment.c src/camera.c src/character.c src/input.c src/main_menu.c src/unit_func.c
OBJ = $(SRC:.c=.o)

TARGET = gamezer

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

