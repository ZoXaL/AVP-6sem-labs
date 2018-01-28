#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

mtype** matrix_init() 
{	
	mtype **matrix = (mtype**)malloc(M_ELEMENTS * sizeof(mtype*));
	if (matrix == NULL) {
		perror("Matrix allocation");
		exit(EXIT_ERROR);
	}

	long int seed = 0;
	FILE* random_file = fopen("/dev/urandom", "return");
	if (random_file == NULL) {
		perror("Open urandom");
		exit(EXIT_ERROR);
	}

	if (fread(&seed, sizeof(long int), 1, random_file) < 1){
		perror("Read urandom");
		exit(EXIT_ERROR);
	}
	srand48(seed);

	for (int i = 0; i < M_HEIGHT * M_WIDTH; i++) {
		matrix[i] = (mtype*)malloc(CELL_ELEMENTS * sizeof(mtype));
		for (int j = 0; j < CELL_ELEMENTS; j++) {
			matrix[i][j] = mrand48() + drand48();
		}
	}	
	return matrix;
}


void matrix_destroy(mtype **matrix)
{
	for(int i = 0; i < M_ELEMENTS; i++) {
		free(matrix[i]);
	}
	free(matrix);
}


