#define _USE_MATH_DEFINES
#include <math.h>
#include "complex.h"

unsigned int _digit_reverse(unsigned int number, unsigned int bits) {
	int count = bits - 2;
	unsigned int ret = number;

	for (number >>= 2; number; number >>= 2) {
		ret <<= 2;
		ret |= number & 3;
		count -= 2;
	}

	ret <<= count;
	ret &= (1 << bits) - 1;

	return ret;
}

void radix4reorder(complex_t *dataIn, complex_t *dataOut, int length) {
	int n, rev;
	int bits = 0;

	for (n = length - 1; n; n >>= 1) {
		bits ++;
	}

#pragma omp parallel default(shared) private(n)
	{
#pragma omp for private(rev) schedule(static)
		for (n = 0; n < length; n ++) {
			rev = _digit_reverse(n, bits);
			_complex_mov(dataIn[rev], dataOut[n]);
		}
	}
}

void radix4(complex_t *data, int length) {
	complex_t butterfly[4], w, temp[4];
	int numOfButterflyes = length;
	int butterflyLen = 1;
	int n, k, butterflyNo, quarter;
	int butterflyOffset, dataOffset[4];
	float angle;

	do {
		numOfButterflyes >>= 2;
		quarter = butterflyLen;
		butterflyLen <<= 2;

#pragma omp parallel default(shared) private(butterflyNo)
		{
#pragma omp for private(butterflyOffset, angle, n, dataOffset, k, w, temp, butterfly) schedule(static)
			for (butterflyNo = 0; butterflyNo < numOfButterflyes; butterflyNo ++) {
				butterflyOffset = butterflyNo * butterflyLen;
				angle = 2.0 * M_PI / (float)butterflyLen;

				for (n = 0; n < quarter; n ++) {
					dataOffset[0] = n + butterflyOffset;
					dataOffset[1] = dataOffset[0] + quarter;
					dataOffset[2] = dataOffset[1] + quarter;
					dataOffset[3] = dataOffset[2] + quarter;

					/* Twiddle factors */
					for (k = 1; k < 4; k ++) {
						w.re = cos(angle * (float)(k*n));
						w.im = sin(angle * (float)(k*n));
						_complex_mul(data[dataOffset[k]], w, temp[k-1]);
					}

					/* Process butterfly */
					butterfly[0].re = data[dataOffset[0]].re + temp[0].re + temp[1].re + temp[2].re;
					butterfly[0].im = data[dataOffset[0]].im + temp[0].im + temp[1].im + temp[2].im;

					butterfly[1].re = data[dataOffset[0]].re - temp[0].im - temp[1].re + temp[2].im;
					butterfly[1].im = data[dataOffset[0]].im + temp[0].re - temp[1].im - temp[2].re;

					butterfly[2].re = data[dataOffset[0]].re - temp[0].re + temp[1].re - temp[2].re;
					butterfly[2].im = data[dataOffset[0]].im - temp[0].im + temp[1].im - temp[2].im;

					butterfly[3].re = data[dataOffset[0]].re + temp[0].im - temp[1].re - temp[2].im;
					butterfly[3].im = data[dataOffset[0]].im - temp[0].re - temp[1].im + temp[2].re;

					/* Place to right position */
					_complex_mov(butterfly[0], data[dataOffset[0]]);
					_complex_mov(butterfly[1], data[dataOffset[1]]);
					_complex_mov(butterfly[2], data[dataOffset[2]]);
					_complex_mov(butterfly[3], data[dataOffset[3]]);
				}
			}
		}
	} while (numOfButterflyes > 1);
}
