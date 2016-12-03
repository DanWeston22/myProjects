//
//  FIRFilter.h
//  CW2
//
//  Created by Dan Weston on 01/12/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#ifndef FIRFilter_h
#define FIRFilter_h

#include <stdio.h>
#include <sndfile.h>

#define NUM_FRAMES 512
#define FIRN 127 //Filter Order Number + 1.

// return buffer index
#define BUFFIX(ix,n) ((ix+n+FIRN)%FIRN)

int sf_error (SNDFILE *sf_file_in) ;

enum errorCode {
    NO_ERROR,
    NEED_HELP,
    BAD_ALLOC,
    BAD_FILE,
    NOT_MONO,
    BAD_INPUT
    // Append this list as necessary.
};

double firCoefficiants (int increment, float fc, float fs);

char* errorText(enum errorCode err);

float sincFunction(float x);

#endif /* FIRFilter_h */
