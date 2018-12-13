#include "complex.h"
#include "radix2.h"
#include "radix4.h"

int isPowerOf4(int i) {
	while (((i & ~3) == i) && (i > 4)) {
		i >>= 2;
	}
	return (i == 4);
}

void fft(complex_t *input, complex_t *output, int length) {
	if (isPowerOf4(length)) {
		radix4reorder(input, output, length);
		radix4(output, length);
	}
	else {
		radix2reorder(input, output, length);
		radix2(output, length);
	}
}
