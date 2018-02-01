#include <stdio.h>

int main() 
{
	double a[2];
	double b[2];
	double c[2];

	a[0] = 1.5f;
	a[1] = 2.5f;

	b[0] = 1.0f;
	b[1] = 2.0f;

	int d = 3;
	int e = 4;
	int f = 0;

	asm volatile(	"movl %1, %%eax; \
			 movl %2, %%ebx; \
			 addl %%ebx, %%eax; \
			 movl %%eax, %0" 
			: "=m"(f) 
			:"r"(d), "r"(e) 
			: "%eax", "%ebx");
	
	printf("%d\n", f);
	//c[0] = a[0] + b[0];
	//c[1] = a[1] + b[1];


	//printf("c[0] = %F, c[1] = %F\n", c[0], c[1]);
	return 0;
}
