//Benchmark.h Header file
#ifndef _BENCHMARK_H
#define _BENCHMARK_H

#include <stdint.h>

void getCpuName(char* str);
int64_t getCpuFrequency(void);
void startMeasure(void);
double getMeasuredTime(void);

#endif /* _BENCHMARK_H */
