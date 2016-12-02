//
//  FIRFilter.c
//  CW2
//
//  Created by Dan Weston on 01/12/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <math.h>
#include "FIRFilter.h"

//Function for sincFunction
float sincFunction(float x){
    if (x==0){
        return 1;
    }
    else{
        return sin(M_PI * x)/(M_PI * x);
    }
}

//Error Status Messages
char* errorText(enum errorCode err) {
    switch (err) {
        case NO_ERROR:
            return "";
        case BAD_ALLOC:
            return "Unable to allocate memory.";
        case BAD_FILE:
            return "Unable to open file.";
        case NOT_MONO:
            return "The input file is not monophonic.";
        case BAD_INPUT:
            return "You entered something erroneous.";
        default:
            return "An unknown error occurred.";
            
    }
    
}
