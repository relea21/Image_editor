#ifndef APPLY_H
#define APPLY_H

#include <stdio.h>
#include "pixel.h"
#include "micunelte.h"

double clamp(double number, int min, int max);

double newpixel(pixel_t **image, int n, int m, int p,
				int maxvalue, char effect[15]);

pixel_t **apply(pixel_t **image, details a);

#endif