#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

char *save_arguments(char *name, int *ascii)
{
	// fct pt a determina daca trb sa salvam ca si fisier binar sau text
	char arguments[100];
	fgets(arguments, 100, stdin);
	*ascii = 0;
	if (strstr(arguments, "ascii"))
		*ascii = 1;
	char *token;
	token = strtok(arguments, "\n ");
	strcpy(name, token);
}

void write_magicword(int ascii, details a, FILE *f)
{
	if (ascii == 1) {
		if (a.values == 1 && a.blackandwhite == 1)
			fprintf(f, "P1\n");
		else if (a.values == 1)
			fprintf(f, "P2\n");
			else
				fprintf(f, "P3\n");

	} else {
		if (a.values == 1 && a.blackandwhite == 1)
			fprintf(f, "P4\n");
		else if (a.values == 1)
			fprintf(f, "P5\n");
			else
				fprintf(f, "P6\n");
	}
}

void write_matrix_text(pixel_t **image, details a, FILE *f)
{
	// scriere intr-un fisier text
	for (int i = 0; i < a.height; i++) {
		for (int j = 0; j < a.widht; j++)
			for (int k = 0; k < a.values; k++) {
				// se aproximeaza rez pt a fi salvate ca si unsigned char
				unsigned char aux;
				aux = round(image[i][j].colors[k]);
				fprintf(f, "%hhu ", aux);
			}
		fprintf(f, "\n");
	}
}

void write_matrix_binar(pixel_t **image, details a, FILE *f)
{
	for (int i = 0; i < a.height; i++)
		for (int j = 0; j < a.widht; j++)
			for (int k = 0; k < a.values; k++) {
				unsigned char aux;
				aux = round(image[i][j].colors[k]);
				fwrite(&aux, sizeof(unsigned char), 1, f);
			}
}

void save(pixel_t **image, details a)
{
	FILE *f;
	char *name;
	int ascii = 0;
	name = malloc(100 * sizeof(char));
	name = save_arguments(name, &ascii);
	f = fopen(name, "wt");
	write_magicword(ascii, a, f);
	if (a.blackandwhite == 1)
		fprintf(f, "%d %d\n", a.widht, a.height);
	else
		fprintf(f, "%d %d\n%d\n", a.widht, a.height, a.maxvalue);
	if (ascii == 1) {
		printf("Saved %s\n", name);
		write_matrix_text(image, a, f);
		fclose(f);
	} else {
		fclose(f);
		FILE *f = fopen(name, "ab");
		printf("Saved %s\n", name);
		write_matrix_binar(image, a, f);
		fclose(f);
	}
	free(name);
}