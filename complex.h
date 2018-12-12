#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <math.h>

#define _complex_mov(src, dest)		(dest).re = (src).re; (dest).im = (src).im

#define _complex_re(x)				((x).re)
#define _complex_im(x)				((x).im)
#define _complex_abs(x)				sqrt(pow((x).re, 2) + pow((x).im, 2))
#define _complex_arg(x)				atan2((x).im, (x).re)

#define _complex_add(a, b, dest)	(dest).re = (a).re + (b).re; (dest).im = (a).im + (b).im
#define _complex_sub(a, b, dest)	(dest).re = (a).re - (b).re; (dest).im = (a).im - (b).im
#define _complex_mul(a, b, dest)	(dest).re = ((a).re * (b).re) - ((a).im * (b).im); (dest).im = ((a).im * (b).re) + ((a).re * (b).im)


typedef struct {
	float re;
	float im;
} complex_t;


void _complex_from_array(float *srcRe, float *srcIm, complex_t *dest, int length);
void _complex_from_real(float *src, complex_t *dest, int length);

#endif /* _COMPLEX_H */
