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
int main(int argc, char* argv[])
{
	char cpuStr[49];				// CPU identification string
	int numOfThreads, n;
	double time, temp_time;
	int size = MIN_SIZE >> 1;
	FILE *file;


	/* Generate square signal */
	generateSquare(in, MAX_SIZE);

	/* Get CPU information */
	getCpuName(cpuStr);
	printf("\nCPU name:                %s", cpuStr);
	printf("\nCPU frequency:           %.2f GHz", (double)getCpuFrequency()/1000000.0);
	printf("\nNumber of cores:         %d", omp_get_num_procs());

#if 1
	fopen_s(&file, "d:/test.csv", "w");

	do {
		size <<= 1;
		printf("\n\nLength of input signal:  %d", size);

		fprintf(file, "\nSize:;%d\nThreads:", size);
		for (numOfThreads = 1; numOfThreads <= 2*omp_get_num_procs(); numOfThreads++) {
			fprintf(file, ";%d", numOfThreads);
		}
#if 1
		fprintf(file,"\nDFT:");
		printf("\n\nDFT:");
		for (numOfThreads = 1; numOfThreads <= 2*omp_get_num_procs(); numOfThreads++) {
			omp_set_num_threads(numOfThreads);
			time = DBL_MAX;
			for (n = 0; n < REPEAT; n++) {
				startMeasure();
				dft(in, out, size);
				temp_time = getMeasuredTime();
				if (temp_time < time) {
					time = temp_time;
				}
			}
			printf("\nNumber of threads: %2d    Time: %.9f s", omp_get_max_threads(), time);
			fprintf(file, ";%.9f", time);
		}
#endif#if 0
		fprintf(file, "\nFFT:");
		printf("\n\nFFT:");
		for (numOfThreads = 1; numOfThreads <= 2*omp_get_num_procs(); numOfThreads++) {
			omp_set_num_threads(numOfThreads);
			time = DBL_MAX;
			for (n = 0; n < REPEAT; n++) {
				startMeasure();
				fft(in, out, size);
				temp_time = getMeasuredTime();
				if (temp_time < time) {
					time = temp_time;
				}
			}
			printf("\nNumber of threads: %2d    Time: %.9f s", omp_get_max_threads(), time);
			fprintf(file, ";%.9f", time);
		}
#endif
	} while (size < MAX_SIZE);

	fclose(file);

	printf("\n\nBenchmark finished. Press ENTER to exit.");
	getchar();
#endif

	return 0;
}



