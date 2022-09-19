#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

void rotate_to_right(pixel_t **image, pixel_t **copy_image, details a)
{
	//fct care roteste la dreapta toata imaginea
	for (int i = 0; i < a.widht; i++)
		for (int j = 0; j < a.height; j++)
			for (int k = 0; k < a.values; k++)
				copy_image[i][j].colors[k] =
								image[a.height - j - 1][i].colors[k];
}

void rotate_to_right_select(pixel_t **image, pixel_t **copy_image, details a)
{
	// fct care roteste doar o selectie
	// aceasta realizeaza transpusa iar mai apoi inverseaza coloanele
	int l;
	for (int i = a.x1; i < a.x2; i++)
		for (int j = a.y1; j < a.y2; j++)
			for (int k = 0; k < a.values; k++)
				copy_image[i - a.x1][j - a.y1].colors[k] =
												image[j][i].colors[k];

	l = a.x2 - a.x1;
	for (int i = 0; i < l ; i++)
		for (int j = 0; j < l / 2; j++)
			for (int k = 0; k < a.values; k++)
				swap_var_double(&copy_image[i][j].colors[k],
								&copy_image[i][l - j - 1].colors[k]);
}

pixel_t **rotate_all_image(pixel_t **image, details *a)
{
	int angle, auxangle = 0;
	scanf("%d", &angle);
	pixel_t **copy_image = NULL;
	//unghiurile negative pot fi vazute ca complementele lor pozitive
	if (angle < 0 && angle > -360)
		auxangle = 360 - (-1 * angle);
	else
		auxangle = angle;
	if (angle > 360 || angle < -360) {
		printf("Unsupported rotation angle\n");

	} else {
		int ok = 0;
		if (auxangle % 360 == 0) {
			printf("Rotated %d\n", angle);
			ok = 1;
		}
		if (auxangle % 360 == 90) {
			printf("Rotated %d\n", angle);
			copy_image = alloc_matrix(a->widht, a->height, a->values);
			rotate_to_right(image, copy_image, *a);
			swap_var(&a->widht, &a->height);
			swap_var(&a->x2, &a->y2);
			free_matrix(image, a->widht, a->height);
			image = copy_image;
			ok = 1;
		}

		//rotirile la 180 270 pot fii vazute ca rotiri la 90 repetate
		if (auxangle % 360 == 180) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 2; i++) {
				copy_image = alloc_matrix(a->widht, a->height, a->values);
				rotate_to_right(image, copy_image, *a);
				swap_var(&a->widht, &a->height);
				swap_var(&a->x2, &a->y2);
				free_matrix(image, a->widht, a->height);
				image = copy_image;
			}
			ok = 1;
		}

		if (auxangle % 360 == 270) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 3; i++) {
				copy_image = alloc_matrix(a->widht, a->height, a->values);
				rotate_to_right(image, copy_image, *a);
				swap_var(&a->widht, &a->height);
				swap_var(&a->x2, &a->y2);
				free_matrix(image, a->widht, a->height);
				image = copy_image;
			}
			ok = 1;
		}
		if (ok == 0)
			printf("Unsupported rotation angle\n");
	}
	return image;
}

void save_new_matrix(pixel_t **image, pixel_t **temp, details a)
{
	for (int i = a.y1; i < a.y2; i++)
		for (int j = a.x1; j < a.x2; j++)
			for (int k = 0; k < a.values; k++)
				image[i][j].colors[k] = temp[i - a.y1][j - a.x1].colors[k];
}

void samematrix(pixel_t **image, pixel_t **temp, details a)
{
	for (int i = a.y1; i < a.y2; i++)
		for (int j = a.x1; j < a.x2; j++)
			for (int k = 0; k < a.values; k++)
				temp[i - a.y1][j - a.x1].colors[k] = image[i][j].colors[k];
}

pixel_t **rotate_a_select(pixel_t **image, details a)
{
	pixel_t **temp = NULL;
	int l, angle, auxangle = 0;
	l = a.x2 - a.x1;
	scanf("%d", &angle);
	if (a.y2 - a.y1 != l) {
		printf("The selection must be square\n");
	} else {
		if (angle < 0 && angle > -360)
			auxangle = 360 - (-1 * angle);
		else
			auxangle = angle;
		if (angle > 360 || angle < -360) {
			printf("Unsupported rotation angle\n");
		} else {
			int ok = 0;
			temp = alloc_matrix(l, l, a.values);
			if (auxangle % 360 == 0) {
				printf("Rotated %d\n", angle);
				samematrix(image, temp, a);
				ok = 1;
			}

			if (auxangle % 360 == 90) {
				printf("Rotated %d\n", angle);
				rotate_to_right_select(image, temp, a);
				ok = 1;
			}

			if (auxangle % 360 == 180) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 2; i++) {
					rotate_to_right_select(image, temp, a);
					save_new_matrix(image, temp, a);
				}
				ok = 1;
			}

			if (auxangle % 360 == 270) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 3; i++) {
					rotate_to_right_select(image, temp, a);
					save_new_matrix(image, temp, a);
				}
				ok = 1;
			}

			if (ok == 0)
				printf("Unsupported rotation angle\n");
			else
				save_new_matrix(image, temp, a);
			free_matrix(temp, l, l);
		}
	}
	return image;
}
