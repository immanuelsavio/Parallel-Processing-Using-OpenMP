#define _USE_MATH_DEFINES

#include <omp.h>
#include <math.h>
#include "complex.h"

void dft(complex_t *input, complex_t *output, int length) {
	int n, k;
	float angle;
	complex_t w, temp;

#pragma omp parallel for default(shared) private(n, w, angle, temp) 
	for (k = 0; k < length; k++) {
		output[k].re = 0;
		output[k].im = 0;
		angle = 2 * M_PI * (float)k / (float)length;
		for (n = 0; n < length; n++) {
			w.re = cos(angle * (float)n);
			w.im = sin(-angle * (float)n);
			_complex_mul(input[n], w, temp);
			_complex_add(output[k], temp, output[k]);
		}
	}
}
