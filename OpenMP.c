// OpenMP.c : Defines the entry point for the console application.
//

#include <omp.h>
#include <stdio.h>
#include <float.h>
#include "dsp.h"
#include "benchmark.h"


#define MIN_SIZE	16
#define MAX_SIZE	8192
#define REPEAT		10

complex_t in[MAX_SIZE];
complex_t out[MAX_SIZE];
float coef[] = {0.0100f, 0.0249f, 0.0668f, 0.1249f, 0.1756f, 0.1957f, 0.1756f, 0.1249f, 0.0668f, 0.0249f, 0.0100f};

void generateSquare(complex_t *signal, int numOfSamples) {
	int n;
	float temp = 1;

	for (n = 0; n < numOfSamples; n++) {
		if (n % 20 == 0) temp *= -1;
		in[n].re = temp;
		in[n].im = 0;
	}
}
