#include <stdio.h>
#include "matrix.h"
#define STATIC_INIT 1

// TODO: 
// + generate matrix of matrix
// * check ifndef about vectorization
// *  
//
int main(int argc, char *argv[]) {
	mtype **matrix1, ** matrix2;
	if (!STATIC_INIT) {
		matrix1 = matrix_init();
		matrix2 = matrix_init();
	} else {
		matrix1 = matric_static_init();
		matrix2 = matric_static_init();
	}

	//printf("First double: %F", matrix[0][0]);
	printf("%s\n", "First matrix:");
	matrix_show(matrix1);
	printf("%s\n", "Second matrix:");
	matrix_show(matrix2);
	mtype **result = matrix_multiply(matrix1, matrix2);
	printf("%s\n", "Result matrix:");
	matrix_show(result);
	matrix_destroy(matrix1);
	matrix_destroy(matrix2);
	matrix_destroy(result);
	return 0;
}

