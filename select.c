#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "micunelte.h"

int the_number(char *arg)
{
	// fct pt a transforma un string in numar
	// si pt a verifica daca este numar
	int number;
	if (strcmp(arg, "0") == 0) {
		number = 0;
	} else {
		number = atoi(arg);
		if (number == 0)
			number = -1;
	}
	return number;
}

void SELECT(details *size)
{
	char arg[100];
	//vedem ce argument urmeaza sa se citeasca
	// in fct de el se executa select sau select all
	scanf("%s", arg);
	if (strcmp(arg, "ALL") == 0) {
		if (size->error == -1) {
			printf("No image loaded\n");
		} else {
			printf("Selected ALL\n");
			select_all_images(size);
		}

	} else {
		int tempx1, tempx2, tempy1, tempy2;
		scanf("%d%d%d", &tempy1, &tempx2, &tempy2);
		tempx1 = the_number(arg);
			if (size->error == -1) {
				printf("No image loaded\n");
			} else {
				int aux, ok = 1;
				//verificam corectitudinea argumentelor
				if (tempx1 < 0 || tempx1 > size->widht) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}

				if (tempx1 == tempx2 && ok == 1) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}
				if (tempy1 == tempy2 && ok == 1) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}

				if ((tempy1 < 0 || tempy1 > size->height) && ok == 1) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}
				if ((tempx2 < 0 || tempx2 > size->widht) && ok == 1) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}

				if ((tempy2 < 0 || tempy2 > size->height) && ok == 1) {
					printf("Invalid set of coordinates\n");
					ok = 0;
				}
				if (ok == 1) {
					if (tempx1 > tempx2) {
						aux = tempx1;
						tempx1 = tempx2;
						tempx2 = aux;
					}

					if (tempy1 > tempy2) {
						aux = tempy1;
						tempy1 = tempy2;
						tempy2 = aux;
					}

					size->x1 = tempx1;
					size->x2 = tempx2;
					size->y1 = tempy1;
					size->y2 = tempy2;

					printf("Selected %d %d %d %d\n",
						   size->x1, size->y1, size->x2, size->y2);
				}
			}
	}
}
