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

mtype* matrix_multiply(mtype *first_matrix, mtype *second_matrix)
{
	mtype* result = matrix_init(true);
	for (int i = 0; i < M_HEIGHT; i++) {
		for (int j = 0; j < M_WIDTH; j++) {
			for (int k = 0; k < M_WIDTH; k++) {
				// printf("i[%d], j[%d], k[%d] = %ld\n", i, j, k, b[j*CELL_WIDTH + k] * a[i*CELL_WIDTH + j]);
				result[i*M_WIDTH + j] += first_matrix[i*M_WIDTH + k] * second_matrix[k*M_WIDTH + j];
			}
		}
	}
	return result;
}

mtype* matrix_multiply_cache(mtype* first_matrix, mtype* second_matrix)
{
	mtype* result = matrix_init(true);
	int blockSize = M_ELEMENTS / B_NUM;
	for(int l = 0; l < B_HEIGHT; l++) {
		for(int m = 0; m < B_WIDTH; m++) {
			for(int n = 0; n < B_WIDTH; n++) {
				for(int i = l * B_HEIGHT; i < (l + 1) * B_HEIGHT; i++) {
					for(int j = m * B_WIDTH; j < (m + 1) * B_WIDTH; j++) {
						for(int k = n * B_WIDTH; k < (n + 1) * B_WIDTH; k++) {
							result[i * M_WIDTH+ j] += first_matrix[i * M_WIDTH + k] *
							 second_matrix[k * M_WIDTH + j];
						}
					}
				}
			}
		}
	}
	/*for (int i = 0; i < M_WIDTH; i++) {
		for (int j = 0; j < M_HEIGHT; j++) {

		}
	}*/
	return result;
}
void matrix_destroy(mtype *matrix)
{
	free(matrix);
}


