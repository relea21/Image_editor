#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
pixel_t **alloc_matrix(int height, int widht, int values)
{
	// alocam spatiu pe o imagine
	pixel_t **image;
	image = malloc(height * sizeof(pixel_t *));
	if (!image)
		fprintf(stderr, "malloc failled\n");
	for (int i = 0; i < height; i++) {
		image[i] = malloc(widht * sizeof(pixel_t));
		if (!image[i]) {
			fprintf(stderr, "malloc failled\n");
			for (int j = 0; j < i; j++)
				free(image[i]);
			free(image);
			}
		for (int j = 0; j < widht; j++)
			image[i][j].colors = malloc(values * sizeof(double));
	}
	return image;
}

void swap_var(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void swap_var_char(double *a, double *b)
{
	double aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void swap_var_double(double *a, double *b)
{
	double aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void free_matrix(pixel_t **image, int height, int widht)
{
	//eliberarea unei imagini din memorie
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < widht; j++)
			free(image[i][j].colors);
		free(image[i]);
	}
	free(image);
}

void select_all_images(details *a)
{
	//se selecteaza toata imaginea
	a->x1 = 0;
	a->x2 = a->widht;
	a->y1 = 0;
	a->y2 = a->height;
}
