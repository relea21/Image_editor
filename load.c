#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

void det_type_of_fille(char *magicword, details *a)
{
	//fct ne ajuta sa determinam daca fisierul citit
	//e text sau binar
	char textfilles[3][3] = {"P1", "P2", "P3"};
	char binaryfilles[3][3] = {"P4", "P5", "P6"};
	for (int i = 0; i < 3; i++)
		if (strcmp(magicword, textfilles[i]) == 0)
			a->type = 1;

	for (int i = 0; i < 3; i++)
		if (strcmp(magicword, binaryfilles[i]) == 0)
			a->type = 2;

	//de asemenea ne ajuta sa determinam daca poza e color sau nu
	if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
		a->values = 1;
		a->blackandwhite = 1;
	}

	if (strcmp(magicword, "P2") == 0 || strcmp(magicword, "P5") == 0) {
		a->values = 1;
		a->blackandwhite = 0;
	}

	if (strcmp(magicword, "P3") == 0 || strcmp(magicword, "P6") == 0) {
		a->values = 3;
		a->blackandwhite = 0;
	}
	//value ->1 (se foloseste doar o culoare)
	//value ->3 (se foloseste 3 culoari)
}

pixel_t **read_binar_images(int height, int widht, FILE *f, int values)
{
	// citire din fisier binar
	pixel_t **image;
	image = alloc_matrix(height, widht, values);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < widht; j++)
			for (int k = 0; k < values; k++) {
				unsigned char aux;
				fread(&aux, sizeof(unsigned char), 1, f);
				image[i][j].colors[k] = aux;
			}
	return image;
}

pixel_t **read_text_images(int height, int widht, FILE *f, int values)
{
	// citire din fisier text
	pixel_t **image;
	image = alloc_matrix(height, widht, values);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < widht; j++)
			for (int k  = 0; k < values; k++) {
				unsigned char aux;
				fscanf(f, "%hhu", &aux);
				image[i][j].colors[k] = aux;
			}
	return image;
}

pixel_t **load_a_image(details *a)
{
	pixel_t **image = NULL;
	char name[100];
	char magicword[3];
	int pose;
	FILE *f;
	scanf("%s", name);
	f = fopen(name, "rt");
	if (!f) {
		printf("Failed to load %s\n", name);
		a->error = -1;
		return NULL;
	}

	fscanf(f, "%s", magicword);
	// determinam ce fel de fiser este
	det_type_of_fille(magicword, a);

	if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
		fscanf(f, "%d%d", &a->widht, &a->height);
	} else {
		fscanf(f, "%d%d", &a->widht, &a->height);
		fscanf(f, "%d", &a->maxvalue);
	}

	pose = ftell(f);
	// retinem pozitia de unde incepe imaginea propriuzisa
	if (a->type == 1) {
		printf("Loaded %s\n", name);
		image = read_text_images(a->height, a->widht, f, a->values);
		select_all_images(a);
		fclose(f);
	}

	if (a->type == 2) {
		fclose(f);
		f = fopen(name, "rb");
		fseek(f, pose + 1, SEEK_SET);
		printf("Loaded %s\n", name);
		image = read_binar_images(a->height, a->widht, f, a->values);
		select_all_images(a);
		fclose(f);
	}

	return image;
}
