#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

#define NWITEMS	64

const char *source = 
"__kernel void memset( __global uint *ds) {"
"	std[get_global_id(0)] = get_global_id(0);"
"}";

int main(int argc, char *argv[])
{
	cl_int cl_errno;

	cl_platform_id platform;
	clGetPlatformIDs(1, &platform, &cl_errno);

	// 2. Find a gpu device
	cl_device_id device;
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &cl_errno);

	cl_uint cu_num;
	size_t wg_size;

	clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &cu_num, NULL);
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &wg_size, NULL);
	printf("cu: %d, wg: %ld\n", cu_num, wg_size);

	// 3. Create a context and command queue on that device
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &cl_errno);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during creating context: %d\n", cl_errno);
		exit(0);
	}
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during createing command queue: %d\n", cl_errno);
		exit(0);
	}

	// 4. Perform runtime source compilation, obtain kernel entry point
	cl_program program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
	clBuildProgram(program, 1, &device, NULL, NULL, &cl_errno);
	if (cl_errno != CL_SUCCESS) {
		printf("Error during creating program: %d\n", cl_errno);
		exit(0);
	}

	char build_log[4096];
	size_t log_length;
	cl_int result2 = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 4096, (void*)build_log, &log_length);
	printf("Got log object: %d. Size: %ld\n%s\n", result2, log_length, build_log);
	cl_kernel kernel = clCreateKernel(program, "memset", NULL);
	// 5. Create a data buffer
	int bsize  = sizeof(cl_uint) * (NWITEMS+1);
	cl_uint *host_buffer = (cl_uint*)malloc(bsize);
	printf("Malloc ptr: %d\n", host_buffer);

	cl_uint hb[NWITEMS];
	memset(host_buffer, 0, bsize);
	
	cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, bsize - sizeof(cl_uint), (void*)host_buffer, &cl_errno);
	printf("Created buffer with errno: %d\n", cl_errno);

	// 6. Launch the kernel
	size_t global_work_size = NWITEMS;
	clSetKernelArg(kernel, 0, bsize, (void*)&buffer);
	clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	clFinish(queue);

	// 7 Look at the results via synchronous buffer map.

	cl_int ptr;
	cl_uint* result = (cl_uint *) clEnqueueMapBuffer(queue, buffer, CL_TRUE, CL_MAP_READ, 0, NWITEMS * sizeof(cl_uint), 0, NULL, NULL, &ptr);

	printf("OK. Before cycle: %d\n", ptr);
	printf("Success: %d\n", ptr == CL_SUCCESS);
	int i;
	for(int i = 0; i < NWITEMS; i++) {
		printf("%d %d\n", i, result[i]);
	}
	return 0;
}
