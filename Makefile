CC = gcc
CFLAGS = -Wall -g `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

SRC = src/main.c src/utils.c src/game.c src/instance.c
OBJ = $(SRC:.c=.o)

TARGET = gamezer

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

