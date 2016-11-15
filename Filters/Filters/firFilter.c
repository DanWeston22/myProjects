//
//  firFilter.c
//  Filters
//
//  Created by Dan Weston on 15/11/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "firFilter.h"

#define FIRN 62

// return buffer index
#define BUFFIX(ix,n) ((ix+n+FIRN)%FIRN)

// the FIR structure
struct fir_s {
    double B[FIRN];
    firFloat X[FIRN];
    firFloat Y[FIRN];
    unsigned int index;
    double fs;
    double fc;
    double Q;
    double peakGain;
};

// private functions
static void fir_calculate(fir* b);

// create a fir
fir* fir_create(
                      int fs,
                      double fc
                      ) {
    
    // allocate fir and return pointer
    fir* b = malloc(sizeof(fir));
    if (b != NULL) {
        
        // put data in structure
        b->fs = fs;
        b->index = 0;
        b->fc = fc;
        
        // clear buffers
        fir_clear(b);
        
        // calculate filter
        fir_calculate(b);
    }
    return b;
}

// destroy the biquad
void fir_destroy(fir* b) {
    free(b);
}

//Structure for sincFunction which then does following maths
double sincFunction // ----- DO SINC FUNCTION HERE ------

for (int number = 0; number < FIRN; number++) {
    //Structure for hamming window which then does following maths
    double hammingWindow = (0.54 - (0.46 * cos(2 * M_PI * number/FIRN)));
    //Structure for sincComponent which then does following maths
    double sincComponent = ((2 * fc)/fs) * sinc(((2 * number) - FIRN)*(fc/fs));
}

// process sample
firFloat fir_process(fir* b, firFloat input) {
    
    double *B = b->B;
    firFloat *X = b->X;
    firFloat *Y = b->Y;
    unsigned int ix = b->index;
    
    // put input on to buffer
    X[BUFFIX(ix,0)] = input;
    
    // process input ----- CORRECT MATHS NEEDS TO GO HERE -----
    for (int incriment = 0; incriment < FIRN; incriment++){
        X[BUFFIX(ix,0)] += B[incriment]*X[BUFFIX(ix,  -incriment)];
    }
    
    // write output
    firFloat output = Y[BUFFIX(ix,0)];
    
    // step through buffer
    b->index = BUFFIX(ix,1);
    
    return output;
}

// set filter parameter - fs
void fir_setFs(fir* b, double fs) {
    b->fs = fs;
    fir_calculate(b);
}

// set filter parameter - fc
void fir_setFc(fir* b, double fc) {
    b->fc = fc;
    fir_calculate(b);
}


// get filter parameter - fs
double fir_getFs(const fir* b) {
    return b->fs;
}

// get filter parameter - fc
double fir_getFc(const fir* b) {
    return b->fc;
}

// clear buffers
void fir_clear(fir* b) {
    // reset buffers
    for (int n = 0; n < FIRN; n++) {
        b->X[n] = 0.0;
        b->Y[n] = 0.0;
    }
}

// calculate filter coefficients
void fir_calculate(fir* b) {
    
    // shorten names
    double *B = b->B;
    double Q = b->Q;
    double fs = b->fs;
    double fc = b->fc;
    
    double w0 = 2.0*M_PI*fc/fs;
    double alpha = sin(w0)/(2.0*Q);
    
    // ------------ Make this FIR_LOWPASS ------------
    
    // source : http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
    
    // BQ_LOWPASS:
            B[0] = (1.0 - cos(w0))/2.0;
            B[1] = 1.0 - cos(w0);
            B[2] = (1.0 - cos(w0))/2.0;


    // normalize
    double norm = B[0];
    for (int i = 0; i < FIRN; i++) {
        B[i] /= norm;
    }
}
