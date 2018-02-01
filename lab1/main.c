#include <stdio.h>
#include <time.h>
#include "matrix.h"
#define STATIC_INIT 0
#define SHOW_MATRIX 0

// TODO: 
// + generate matrix of matrix
// * check ifndef about vectorization
// *  
//
int main(int argc, char *argv[]) {
	clock_t start_time, end_time;
	mtype **matrix1, ** matrix2;
	if (!STATIC_INIT) {
		matrix1 = matrix_init();
		matrix2 = matrix_init();
	} else {
		matrix1 = matric_static_init();
		matrix2 = matric_static_init();
	}
 
 	if (SHOW_MATRIX) {
		printf("%s\n", "First matrix:");
		matrix_show(matrix1);
		printf("%s\n", "Second matrix:");
		matrix_show(matrix2);
	}
	start_time = clock();
	mtype **result = matrix_multiply(matrix1, matrix2);
	end_time = clock();
	printf("time in colcks: %ld\n", end_time - start_time);
	printf("time in seconds: %f\n", 
		(double) (end_time - start_time) / CLOCKS_PER_SEC);
	if (SHOW_MATRIX) {
		printf("%s\n", "Result matrix:");
		matrix_show(result);
	}
	matrix_destroy(matrix1);
	matrix_destroy(matrix2);
	matrix_destroy(result);
	return 0;
}

