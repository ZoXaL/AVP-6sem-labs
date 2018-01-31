#include <stdio.h>
#include "matrix.h"

// TODO: 
// + generate matrix of matrix
// * check ifndef about vectorization
// *  
//
int main(int argc, char *argv[]) {
	mtype** matrix = matrix_init();
	//printf("First double: %F", matrix[0][0]);
	matrix_show(matrix);
	matrix_destroy(matrix);
	return 0;
}

