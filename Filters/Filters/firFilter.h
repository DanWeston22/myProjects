//
//  firFilter.h
//  Filters
//
//  Created by Dan Weston on 15/11/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#ifndef firFilter_h
#define firFilter_h

#include <stdio.h>

// FIR type
typedef struct fir_s fir;

// biquad sample type (floating point)
typedef float firFloat;

// create a FIR
extern fir* fir_create(
                       int fs,
                       double fc,
                       );

// destroy the fir
extern void fir_destroy(fir* b);

// process sample
extern firFloat fir_process(fir* b, firFloat input);

// set filter parameters
extern void fir_setFs(fir* b, double fs);
extern void fir_setFc(fir* b, double fc);

// clear buffers
extern void fir_clear(fir* b);

#endif /* firFilter_h */
