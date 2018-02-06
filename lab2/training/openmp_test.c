#include <stdio.h>
#include <omp.h>

int    main()
{
	#pragma omp parallel
	printf("Hello OpenMP!\n");
	return 0;
}
