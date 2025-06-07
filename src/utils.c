#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float distance(Coordinate a, Coordinate b) {
	float square = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	return pow(square, .5);
}

char* read_file(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }

    long filesize = ftell(file);
    if (filesize < 0) {
        fclose(file);
        return NULL;
    }
    rewind(file);

    char *buffer = malloc(filesize + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, filesize, file);
    fclose(file);

    if (read_size != (size_t)filesize) {
        free(buffer);
        return NULL;
    }

    buffer[filesize] = '\0';
    return buffer;
}
