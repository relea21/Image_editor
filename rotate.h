#ifndef ROTATE_H
#define ROTATE_H

#include <stdio.h>
#include "pixel.h"
#include "micunelte.h"

void rotate_to_right(pixel_t **image, pixel_t **copy_image, details a);

void rotate_to_right_select(pixel_t **image, pixel_t **copy_image, details a);

pixel_t **rotate_all_image(pixel_t **image, details *a);

void save_new_matrix(pixel_t **image, pixel_t **temp, details a);

void samematrix(pixel_t **image, pixel_t **temp, details a);

pixel_t **rotate_a_select(pixel_t **image, details a);

#endif