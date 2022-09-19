#ifndef PIXEL_H
#define PIXEL_H

typedef struct {
	// colors va retine culorile pt pixeli
	double *colors;
} pixel_t;
typedef struct {
	//datele auxiliare pt o imagine
	int x1, x2, y1, y2, height, widht, maxvalue, error;
	int type, values;
	int blackandwhite;
	// error ne spune daca este sau nu incarcata o imagine
} details;

#endif