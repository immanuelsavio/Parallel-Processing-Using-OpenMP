#ifndef _DSP_H
#define _DSP_H

#include "complex.h"

void fir(float *input, float *output, float *coef, int numOfSamples, int numOfCoef);
void dft(complex_t *input, complex_t *output, int length);
void fft(complex_t *input, complex_t *output, int length);

#endif /* _DSP_H */
