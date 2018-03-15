#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

mtype* matrix_create(int h, int w)
{
	mtype* matrix = (mtype*)malloc(w * h * sizeof(mtype));
	if (matrix == NULL) {
		return NULL;
	}

	for (int i = 0; i < w * h; i++) {
		matrix[i] = 7;
	}

	return matrix;
}

void matrix_release(mtype* matrix)
{
	free(matrix);
}

void matrix_show(mtype* matrix, int h, int w)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (j < 20) {
				printf("%d ", matrix[i * w + j]);
			}
		}
		printf("\n");
	}
}
