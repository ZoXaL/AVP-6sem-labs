#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

static long int random_seed = 0;

mtype* matrix_init(bool zero) 
{	
	mtype *matrix = (mtype*)malloc(M_ELEMENTS * sizeof(mtype));
	if (matrix == NULL) {
		perror("Matrix allocation");
		exit(EXIT_ERROR);
	}
	if (random_seed == 0) {
		FILE* random_file = fopen("/dev/urandom", "return");
		if (random_file == NULL) {
			perror("Open urandom");
			exit(EXIT_ERROR);
		}

		if (fread(&random_seed, sizeof(long int), 1, random_file) < 1){
			perror("Read urandom");
			exit(EXIT_ERROR);
		}
		fclose(random_file);

		srand48(random_seed);
	}
	
	if (zero) {
		for (int i = 0; i < M_ELEMENTS; i++) {
			matrix[i] = 0;	
		}	
	} else {
		for (int i = 0; i < M_ELEMENTS; i++) {
			matrix[i] = mrand48() + drand48();		
		}	
	}
	return matrix;
}

mtype* matric_static_init()
{
	mtype *matrix = (mtype*)malloc(M_ELEMENTS * sizeof(mtype));
	if (matrix == NULL) {
		perror("Matrix allocation");
		exit(EXIT_ERROR);
	}

	for (int i = 0; i < M_ELEMENTS; i++) {
		matrix[i] = i + 1;
	}	
	return matrix;
}

void matrix_show(mtype *matrix)
{
	for (int i = 0; i < M_HEIGHT; i++) {
		for (int j = 0; j < M_WIDTH; j++) {
			printf("%16.1F", matrix[i * M_WIDTH + j]);
		}
		printf("\n");
	}
}

void matrix_destroy(mtype **matrix)
{
	free(matrix);
}


