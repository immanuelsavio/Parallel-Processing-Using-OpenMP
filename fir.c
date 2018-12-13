#include <omp.h>

void fir(float *input, float *output, float *coef, int numOfSamples, int numOfCoef) {
	int i, j;
#pragma omp parallel for private(j)
	for (i = 0; i < numOfSamples; i++) {
		output[i] = 0;
		for (j = 0; j < numOfCoef; j++) {
			if (i-j >= 0) {
				output[i] += input[i-j] * coef[j];
			}
		}
	}
}
