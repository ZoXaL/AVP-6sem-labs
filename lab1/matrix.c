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

mtype** matric_static_init()
{
	mtype **matrix = (mtype**)malloc(M_ELEMENTS * sizeof(mtype*));
	if (matrix == NULL) {
		perror("Matrix allocation");
		exit(EXIT_ERROR);
	}

	for (int i = 0; i < M_HEIGHT * M_WIDTH; i++) {
		matrix[i] = (mtype*)malloc(CELL_ELEMENTS * sizeof(mtype));
		for (int j = 0; j < CELL_ELEMENTS; j++) {
			matrix[i][j] = i + j + 1;
		}
	}	
	return matrix;
}
void matrix_show(mtype **matrix)
{
	for (int i = 0; i < M_HEIGHT; i++) {
		for (int j = 0; j < M_WIDTH; j++) {
			printf("Matrix at [%d][%d]:\n", i, j);
			for (int k = 0; k < CELL_HEIGHT; k++) {
				for (int l = 0; l < CELL_WIDTH; l++) {
					printf("%16.1F", matrix[i * M_WIDTH + j][k * CELL_WIDTH + l]);
				}
				printf("\n");
			}
			printf("------------------");
			printf("------------------\n");
		}
	}
}

mtype** matrix_multiply(mtype ** first_matrix, mtype ** second_matrix)
{
	mtype** result = matrix_init();
	for (int i = 0; i < M_HEIGHT; i++) {
		for (int j = 0; j < M_WIDTH; j++) {
			for (int k = 0; k < CELL_HEIGHT; k++) {
				for (int m = 0; m < CELL_HEIGHT; m++) {
					mtype res_el = 0;
					for (int l = 0; l < CELL_WIDTH; l++) {
						res_el += (first_matrix[i * M_WIDTH + j][k * CELL_WIDTH + l] *
							second_matrix[i * M_WIDTH + j][l * CELL_WIDTH + m]);
					}
					result[i * M_WIDTH + j][k * CELL_WIDTH + m] = res_el;
				}
			}
		}
	}
	return result;
}

void matrix_destroy(mtype **matrix)
{
	for(int i = 0; i < M_ELEMENTS; i++) {
		free(matrix[i]);
	}
	free(matrix);
}


