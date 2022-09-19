#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include "pixel.h"
#include "micunelte.h"

char *save_arguments(char *name, int *ascii);

void write_magicword(int ascii, details a, FILE *f);

void write_matrix_text(pixel_t **image, details a, FILE *f);

void write_matrix_binar(pixel_t **image, details a, FILE *f);

void save(pixel_t **image, details a);

#endif