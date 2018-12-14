#define _USE_MATH_DEFINES
#include <math.h>
#include "complex.h"

unsigned int _bit_reverse(unsigned int number, unsigned int bits) {
	int count = bits - 1;
	unsigned int ret = number;

	for (number >>= 1; number; number >>= 1) {
		ret <<= 1;
		ret |= number & 1;
		count --;
	}

	ret <<= count;
	ret &= (1 << bits) - 1;

	return ret;
}

void radix2reorder(complex_t *dataIn, complex_t *dataOut, int length) {
	int n, rev;
	int bits = 0;

	for (n = length - 1; n; n >>= 1) {
		bits ++;
	}

#pragma omp parallel default(shared) private(n)
	{
#pragma omp for private(rev) schedule(static)
		for (n = 0; n < length; n ++) {
			rev = _bit_reverse(n, bits);
			_complex_mov(dataIn[rev], dataOut[n]);
		}
	}
}

void radix2(complex_t *data, int length) {

	complex_t w, temp, butterfly[2];
	int n, half, halfOffset, dataOffset;
	int butterflyNo, butterflyOffset;
	int bits = 0;
	int numOfButterflyes = length;
	int butterflyLen = 1;
	float angle;

	/* Get number of bits representing length */
	for (n = length - 1; n; n >>= 1) {
		bits ++;
	}

	do {
		numOfButterflyes >>= 1;
		half = butterflyLen;
		butterflyLen <<= 1;

#pragma omp parallel default(shared) private(butterflyNo)
		{
#pragma omp for private(butterflyOffset, angle, n, dataOffset, halfOffset, w, temp, butterfly) schedule(static)
			for (butterflyNo = 0; butterflyNo < numOfButterflyes; butterflyNo ++) {
				butterflyOffset = butterflyNo * butterflyLen;
				angle = 2.0 * M_PI / (float)butterflyLen;

				for (n = 0; n < half; n ++) {
					dataOffset = n + butterflyOffset;
					halfOffset = dataOffset + half;

					/* Twiddle factor */
					w.re = cos(angle * (float)n);
					w.im = sin(angle * (float)n);

					/* Proccess butterfly */
					_complex_mul(data[halfOffset], w, temp);
					_complex_add(data[dataOffset], temp, butterfly[0]);
					_complex_sub(data[dataOffset], temp, butterfly[1]);

					/* Butterfly output to correct position */
					_complex_mov(butterfly[0], data[dataOffset]);
					_complex_mov(butterfly[1], data[halfOffset]);
				}
			}
		}

	} while (numOfButterflyes > 1);
}
