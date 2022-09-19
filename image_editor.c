#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"
#include "load.h"
#include "select.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"

void clear_junk(void)
{
	// curata ce a ramas pe linie in urma unei comenzi invalide
	char junk;
	scanf("%c", &junk);
	while (junk != '\n')
		scanf("%c", &junk);
}

int main(void)
{
	pixel_t **image = NULL;
	details size;
	char operation[100];
	scanf("%s", operation);
	char arguments[7][7] = {"LOAD", "SELECT", "ROTATE", "CROP", "APPLY",
									"SAVE", "EXIT"};
	int sw = 1;
	size.error = -1;
	// se pleaca cu size.error -1 pt ca initial nu
	// e incarcata nicio matrice
	while (sw == 1) {
		int ok = 0;
		for (int i = 0; i < 7; i++)
			if (strcmp(operation, arguments[i]) == 0)
				ok = 1;
		if (ok == 0) {
			printf("Invalid command\n");
			clear_junk();
		}
		if (strcmp(operation, "LOAD") == 0) {
			if (image)
				free_matrix(image, size.height, size.widht);
			size.error = 0;
			image = load_a_image(&size);
		}
		if (strcmp(operation, "SELECT") == 0)
			SELECT(&size);
		if (strcmp(operation, "ROTATE") == 0) {
			if (size.error == -1) {
				printf("No image loaded\n");
				clear_junk();
			} else {
				if (size.x1 == 0 && size.x2 == size.widht &&
					size.y1 == 0 && size.y2 == size.height)
					image = rotate_all_image(image, &size);
				else
					image = rotate_a_select(image, size);
			}
		}
		if (strcmp(operation, "CROP") == 0)
			if (size.error == -1)
				printf("No image loaded\n");
			else
				image = crop(image, &size);
		if (strcmp(operation, "APPLY") == 0)
			if (size.error == -1) {
				printf("No image loaded\n");
				clear_junk();
			} else {
				char control;
				scanf("%c", &control);
				if (control == '\n')
					printf("Invalid command\n");
				else
					image = apply(image, size);
			}
		if (strcmp(operation, "SAVE") == 0) {
			if (size.error == -1) {
				printf("No image loaded\n");
				clear_junk();
			} else {
				save(image, size);
			}
		}
		if (strcmp(operation, "EXIT") == 0) {
			if (size.error == -1)
				printf("No image loaded\n");
			sw = 0;
			break;
		}
		scanf("%s", operation);
	}
	// la final se elibereaza matricea incarcata in memorie
	if (image)
		free_matrix(image, size.height, size.widht);
	return 0;
}
