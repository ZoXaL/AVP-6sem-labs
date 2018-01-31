#ifndef MATRIX_H
#define MATRIX_H

#define M_HEIGHT 	2//50
#define M_WIDTH 	2//50
#define M_ELEMENTS	(M_HEIGHT * M_WIDTH)
#define CELL_HEIGHT	4
#define CELL_WIDTH 	4
#define CELL_ELEMENTS	(CELL_HEIGHT * CELL_WIDTH)

#define EXIT_ERROR	1

typedef double mtype;

mtype** matrix_init();

void matric_show();

void matrix_destroy();

#endif
