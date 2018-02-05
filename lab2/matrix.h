#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/* Kirill's proc: 4 threads, cashe3 - 3MB, cashe2 - 2*256KB,
cashe1(data) - 2*32KB.
*/

#define M_HEIGHT	4
#define M_WIDTH 	4
#define M_ELEMENTS	(M_HEIGHT * M_WIDTH)

#define EXIT_ERROR	1

typedef double mtype;

mtype* matrix_init(bool);

mtype* matric_static_init();

void matrix_show(mtype*);

void matrix_destroy();

#endif