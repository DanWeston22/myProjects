#ifndef FIRFilter_h
#define FIRFilter_h

#include <stdio.h>

#define NUM_FRAMES 512
#define FIRN 127 //Filter Order Number + 1.

typedef struct fir_s {
    float x[FIRN];
    float b[FIRN];
    unsigned int index;
} fir;

void fir_calculate(fir *f, float fs, float fc);

float fir_process(fir *f, float x);

void fir_processBlock(fir *f, float * buffer, unsigned int length, unsigned int step);

#endif /* FIRFilter_h */
