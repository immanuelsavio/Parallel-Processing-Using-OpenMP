#include <omp.h>
#include "complex.h"

void _complex_from_array(float *srcRe, float *srcIm, complex_t *dest, int length) {
	int n;
	for (n = 0; n < length; n ++) {
		dest[n].re = srcRe[n];
		dest[n].im = srcIm[n];
	}
}
void _complex_from_real(float *src, complex_t *dest, int length) {
	int n;

	for (n = 0; n < length; n ++) {
		dest[n].re = src[n];
		dest[n].im = 0;
	}
}
