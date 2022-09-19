#ifndef MICUNELTE_H
#define MICUNELTE_H

#include <stdio.h>
#include "pixel.h"

pixel_t **alloc_matrix(int height, int widht, int values);

void swap_var(int *a, int *b);

void swap_var_char(double *a, double *b);

void select_all_images(details *a);

void swap_var_double(double *a, double *b);

void free_matrix(pixel_t **image, int height, int widht);

void select_all_images(details *a);

#endif
