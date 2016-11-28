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
#define fc 1000


// return buffer index
#define BUFFIX(ix,n) ((ix+n+FIRN)%FIRN)

// the FIR structure
struct fir_s {
    double B[FIRN];
    firFloat X[FIRN];
    firFloat Y[FIRN];
    unsigned int index;
    double fs;
    //double fc;
    double Q;
    double peakGain;
};

int sinc(double x);

// private functions
static void fir_calculate(fir* b);

// create a fir
fir* fir_create(
                      int fs
                      //double fc
                      ) {
    
    
                          
    // allocate fir and return pointer
    fir* b = malloc(sizeof(fir));
    if (b != NULL) {
        
        // put data in structure
        b->fs = fs;
        b->index = 0;
        //b->fc = fc;
        
        // clear buffers
        fir_clear(b);
        
        // calculate filter
        fir_calculate(b);
    }
                          
    //Function for filter coefficiants
                          
    double b[FIRN];
    for (int incriment = 0; incriment < FIRN; incriment++){
    //Structure for hamming window which then does following maths
    double hammingWindow = (0.54 - (0.46 * cos(2 * M_PI * incriment/FIRN)));
    //Structure for sincComponent which then does following maths
    double x = ((2 * incriment) - FIRN)*(fc/fs);
    double sincComponent = ((2 * fc)/fs) * sinc(x);
    b[incriment] = (hammingWindow + sincComponent);
    }
    return b;
}

// destroy the biquad
void fir_destroy(fir* b) {
    free(b);
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
        Y[BUFFIX(ix,0)] += B[incriment]*X[BUFFIX(ix,  -incriment)];
    }
    
    // write output
    firFloat output = Y[BUFFIX(ix,0)];
    
    // step through buffer
    b->index = BUFFIX(ix,1);
    
    return output;
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

    // normalize
    double norm = B[0];
    for (int i = 0; i < FIRN; i++) {
        B[i] /= norm;
    }
}
