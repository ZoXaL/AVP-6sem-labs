#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#include "matrix.h"

static long int random_seed = 0;

