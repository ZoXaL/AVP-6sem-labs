#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>

#include "matrix.h"

#define EXIT_ERROR	1


#define N 5//100000
#define BYTES_IN_KB				1024
#define BYTES_IN_MB				1024 * 1024
#define MAX_CACHE_WAY			20
#define CACHE_SIZE_KB		 	 64
#define DELIMETER_SIZE_BYTES		BYTES_IN_MB - STR_SIZE_BYTES
#define CELL_SIZE_BYTES	     	 64
#define CELL_PER_STR	(CACHE_SIZE_KB * BYTES_IN_KB) / (MAX_CACHE_WAY * CELL_SIZE_BYTES)
#define STR_SIZE_BYTES CELL_PER_STR * CELL_SIZE_BYTES

struct unit 
{
	u_int64_t space_taker[7];
	struct unit* next;
};

struct unit *mass;

void init_mass()
{
	mass = (struct unit*) malloc(MAX_CACHE_WAY * BYTES_IN_MB);
}

void prepare_mass_to_way(int way)
{
	for (int i = 0; i < CELL_PER_STR; i++) {
		for (int j = 0; j < way; j++) {
			if (j < way - 1) {
				((struct unit*)((char*)mass + i * CELL_SIZE_BYTES + (j * BYTES_IN_MB)))->next = 
					(struct unit*)((char*)mass + i * CELL_SIZE_BYTES + ((j + 1) * BYTES_IN_MB));
			} else {
				if (i < CELL_PER_STR - 1) {
					((struct unit*)((char*)mass  + i * CELL_SIZE_BYTES + (j * BYTES_IN_MB)))->next =
						(struct unit*)((char*)mass + (i + 1) * CELL_SIZE_BYTES);					
				} else {
					((struct unit*)((char*)mass  + i * CELL_SIZE_BYTES + (j * BYTES_IN_MB)))->next = mass;
				}
			}

		}
	}
}

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

double measure_way_time(int way)
{
	unsigned long long start_time;
	struct unit *tmp = mass;
	start_time = rdtsc();
	volatile int i = 0;
	for (int k = 0; k < N; k++) {
		for (i = 0; i < MAX_CACHE_WAY * CELL_PER_STR; i++) {
			tmp = tmp->next;
		}
	}
	return (double) (rdtsc() - start_time) / (N * MAX_CACHE_WAY * CELL_PER_STR);
}

int main(int argc, char *argv[]) {
	init_mass();
	printf("Unit size:%ld\n", sizeof(struct unit));
	prepare_mass_to_way(9);
	double ans = measure_way_time(9);
	printf("res: %f\n", ans);
	return 0;
}
