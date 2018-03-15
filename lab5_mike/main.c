#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

#include "cl_api.h"
#include "matrix.h"


int main(int argc, char *argv[])
{
	cl_platform_id platform_id = get_platform_id();
	if (call_errno != CALL_SUCCESS) {
		goto exit;
	}

	cl_device_id device_id = get_device_id(platform_id);
	if (call_errno != CALL_SUCCESS) {
		goto exit;
	}
	size_t group_size = 4;//get_device_group_size(device_id);
	printf("Device group size: %ld\n", group_size);

	cl_context context = clCreateContext(
				NULL, 1, &device_id, NULL, NULL, &cl_errno
	);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during creating context: %d\n", cl_errno);
		goto exit;
	}

	cl_command_queue queue = clCreateCommandQueue(context, device_id, 0, NULL);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during creating command queue: %d\n", cl_errno);
		goto context_release;
	}
	
	mtype *source_matrix = matrix_create(MATRIX_WIDTH, MATRIX_HEIGHT);

	cl_mem matrix_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, MATRIX_SIZE_BYTES, source_matrix, &cl_errno);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during buffer allocation\n");
		goto matrix_release;
	}

	cl_program program = get_cl_program(context, "int_img.cl");
	cl_errno = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during building program: %d\n", cl_errno);
		exit(0);
	}

	size_t matrix_height = MATRIX_HEIGHT;
	size_t matrix_width = MATRIX_WIDTH;

	long int vertical_invocations = matrix_height / group_size;
	if (matrix_height % group_size != 0) vertical_invocations++;

	const size_t vertical_task_size[2] = 	{MATRIX_WIDTH,	4};
	const size_t vertical_group_size[2] = {1, 						4};

//__kernel void image_vertical(
//										__global int *data
//										__global __read_only long int mheight
//										__global __read_only long int mwidth
//										__global __read_only int i) {
//	data[i * mheight + get_local_id(1) * mwidth + get_local_id(0)] = get_local_id(1);
//}
	int i = 0;
	//for (int i = 0, h = matrix_height; h > 0; i++, h-=group_size) {
		cl_kernel kernel = clCreateKernel(program, "image_vertical", NULL);
		clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&matrix_buffer);
		clSetKernelArg(kernel, 1, sizeof(long int), (void*)&matrix_height);
		clSetKernelArg(kernel, 2, sizeof(long int), (void*)&matrix_width);
		clSetKernelArg(kernel, 3, sizeof(int), (void*)&i);
		
		clEnqueueNDRangeKernel(
								queue, 
								kernel, 
								2, 
								NULL, 
								vertical_task_size, 
								vertical_group_size, 
								0, 
								NULL, 
								NULL
		);
		//clFinish(queue);
	//}
//	do {
//
//		
//	} while (matrix_height > vertical_group_size);

	clFinish(queue);

	mtype result_matrix[MATRIX_WIDTH * MATRIX_HEIGHT];
	cl_errno = clEnqueueReadBuffer(
									queue, 
									matrix_buffer, 
									CL_BLOCKING, 
									0, 
									MATRIX_SIZE_BYTES, 
									result_matrix, 
									0,
									NULL, 
									NULL
	);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during reading result matrix: %d\n", cl_errno);
		goto matrix_release;
	}
	clFinish(queue);
	printf("====\n");
	matrix_show(result_matrix, MATRIX_HEIGHT, MATRIX_WIDTH);

cl_program_release:
	clReleaseProgram(program);
cl_buffer_release:
	clReleaseMemObject(matrix_buffer);
matrix_release:
	matrix_release(source_matrix);
queue_release:
	clReleaseCommandQueue(queue);
context_release:
	clReleaseContext(context);
exit:
	return 0;
}
