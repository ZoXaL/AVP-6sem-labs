#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_WIDTH			8
#define MATRIX_HEIGHT			16
#define MATRIX_SIZE_BYTES	sizeof(mtype) * MATRIX_WIDTH * MATRIX_HEIGHT

typedef int mtype;

mtype* matrix_create(int h, int w);
void matrix_release(mtype*);
void matrix_show(mtype*, int h, int w);

#endif
