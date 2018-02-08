#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/* Kirill's proc: 4 threads, cache3 - 3MB, cache2 - 256KB,
cache1(data) - 2*32KB.
*/

/*
Mike proc: 
* 2 cores
* L1i — 64KB
* L1d — 64KB
* L2 — 1024KB 
*/

#define BLOCK_SIZE = 1024

#define EXIT_ERROR	1

struct unit 
{
	double space_taker[7];
	struct unit* next;
	int space_taker2;
};


#endif
