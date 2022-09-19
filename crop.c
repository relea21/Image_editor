#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

pixel_t **crop(pixel_t **image, details *a)
{
	pixel_t **copy_image;
	if (a->error == -1) {
		printf("No image loaded\n");
		return NULL;
	}
	copy_image = alloc_matrix(a->y2 - a->y1, a->x2 - a->x1, a->values);
	for (int i = a->y1; i < a->y2; i++)
		for (int j = a->x1; j < a->x2; j++)
			for (int k = 0; k < a->values; k++)
				copy_image[i - a->y1][j - a->x1].colors[k] =
													image[i][j].colors[k];

	free_matrix(image, a->height, a->widht);
	a->height = a->y2 - a->y1;
	a->widht = a->x2 - a->x1;
	select_all_images(a);
	image = copy_image;
	printf("Image cropped\n");
	return image;
}
