#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

double clamp(double number, int min, int max)
{
	if (number < min)
		return min;
	if (number > max)
		return max;
	return number;
}

double newpixel(pixel_t **image, int n, int m, int p,
				int maxvalue, char effect[15])
{
	// acestea sunt matricile ajutatoare pt aplicarea efectelor
	double mat_gblur[3][3] = {1 / 16., 2 / 16., 1 / 16., 2 / 16., 4 / 16.,
										 2 / 16., 1 / 16., 2 / 16., 1 / 16.};
	double mat_blur[3][3] = {1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9.,
										 1 / 9., 1 / 9., 1 / 9., };
	double mat_sharpen[3][3] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
	double mat_edge[3][3] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	double newpixel = 0;

	if (strcmp(effect, "GAUSSIAN_BLUR") == 0) {
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				newpixel = newpixel + (double)image[n + i][m + j].colors[p]
													* mat_gblur[i + 1][j + 1];
			}
	newpixel = clamp(newpixel, 0, maxvalue);
	}

	if (strcmp(effect, "BLUR") == 0) {
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				newpixel = newpixel + (double)image[n + i][m + j].colors[p]
													 * mat_blur[i + 1][j + 1];
			}
	newpixel = clamp(newpixel, 0, maxvalue);
	}

	if (strcmp(effect, "SHARPEN") == 0) {
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				newpixel = newpixel + (double)image[n + i][m + j].colors[p]
												* mat_sharpen[i + 1][j + 1];
			}
	newpixel = clamp(newpixel, 0, maxvalue);
	}

	if (strcmp(effect, "EDGE") == 0) {
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				newpixel = newpixel + (double)image[n + i][m + j].colors[p]
													* mat_edge[i + 1][j + 1];
			}
	newpixel = clamp(newpixel, 0, maxvalue);
	}

	return newpixel;
}

pixel_t **apply(pixel_t **image, details a)
{
	pixel_t **copy_image;
	char effect[15];
	scanf("%s", effect);
	int sw = 0;
	char option[4][15] = {"GAUSSIAN_BLUR", "BLUR", "EDGE", "SHARPEN"};
	for (int i = 0; i < 4; i++)
		if (strcmp(option[i], effect) == 0)
			sw = 1;
	if (sw == 0) {
		printf("APPLY parameter invalid\n");
	} else {
		if (a.values == 3) {
			printf("APPLY %s done\n", effect);
		copy_image = alloc_matrix(a.height, a.widht, a.values);
		for (int i = 0; i < a.height; i++)
			for (int j = 0; j < a.widht; j++)
				for (int k = 0; k < a.values; k++)
					copy_image[i][j].colors[k] = image[i][j].colors[k];

		for (int i = a.y1; i < a.y2; i++)
			for (int j = a.x1; j < a.x2; j++)
				if (i >= 1 && i <= a.height - 2 && j >= 1 && j <= a.widht - 2)
					for (int k = 0; k < 3; k++)
						copy_image[i][j].colors[k] =
								newpixel(image, i, j, k, a.maxvalue, effect);

		free_matrix(image, a.height, a.widht);
		image = copy_image;
		} else {
			printf("Easy, Charlie Chaplin\n");
		}
	}
	return image;
}
