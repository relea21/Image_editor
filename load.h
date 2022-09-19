#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include "pixel.h"
#include "micunelte.h"

void det_type_of_fille(char *magicword, details *a);

pixel_t **read_binar_images(int height, int widht, FILE *f, int values);

pixel_t **read_text_images(int height, int widht, FILE *f, int values);

pixel_t **load_a_image(details *a);

#endif