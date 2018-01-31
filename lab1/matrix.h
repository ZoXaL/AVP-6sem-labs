#ifndef MATRIX_H
#define MATRIX_H

#define M_HEIGHT 	5//50
#define M_WIDTH 	5//50
#define M_ELEMENTS	(M_HEIGHT * M_WIDTH)
#define CELL_HEIGHT	4
#define CELL_WIDTH 	4
#define CELL_ELEMENTS	(CELL_HEIGHT * CELL_WIDTH)

#define EXIT_ERROR	1

typedef double mtype;

mtype** matrix_init();

mtype** matric_static_init();

void matric_show();

mtype** matric_multiply();

void matrix_destroy();

#endif
