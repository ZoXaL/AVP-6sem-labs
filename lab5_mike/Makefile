opencl_flags := -Wno-deprecated-declarations

main: clean main.c cl_api.c matrix.c
	gcc main.c cl_api.c matrix.c -o $@ ${opencl_flags} -lOpenCL

mf: main_first.c
	gcc main_first.c -o $@ ${opencl_flags} -lOpenCL

tmp: tmp.c matrix.c
	g++ tmp.c matrix.c -o $@ ${opencl_flags} -lOpenCL -I${AMDAPPSDKROOT}/include

.PHONY: clean

clean:
	rm -f main
