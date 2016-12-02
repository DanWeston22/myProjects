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

enum errorCode {
    NO_ERROR,
    BAD_ALLOC,
    BAD_FILE,
    NOT_MONO,
    BAD_INPUT
    // Append this list as necessary.
};

char* errorText(enum errorCode err);

float sincFunction(float x);

#endif /* FIRFilter_h */
