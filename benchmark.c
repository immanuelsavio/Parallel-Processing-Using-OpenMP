#include <string.h>
#include <Windows.h>
#include <intrin.h>
#include "benchmark.h"

static __int64 startCounter;

const char* timeUnits[] = {
	"s",
	"ms",
	"us",
	"ns",
	"ps"
};

void getCpuName(char* str) {
	char tempStr[49];
	char *ptr = tempStr;

	memset(tempStr, 0, 49);
	__cpuid((int*)tempStr, 0x80000002);
	__cpuid((int*)(tempStr+16), 0x80000003);
	__cpuid((int*)(tempStr+32), 0x80000004);

	while (*ptr == ' ') {
		ptr ++;
	}
	strcpy(str, ptr);
}

int64_t getCpuFrequency(void) {
	int64_t freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	return freq;
}

void startMeasure(void) {
	QueryPerformanceCounter((LARGE_INTEGER*)&startCounter);
}

double getMeasuredTime(void) {
	int64_t stopCounter;

	QueryPerformanceCounter((LARGE_INTEGER*)&stopCounter);

	return (double)(stopCounter - startCounter) / (double)getCpuFrequency();
}
