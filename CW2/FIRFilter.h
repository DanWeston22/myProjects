#ifndef FIRFilter_h
#define FIRFilter_h

#include <stdio.h>
#include <sndfile.h>

#define NUM_FRAMES 512
#define FIRN 127 //Filter Order Number + 1.

// return buffer index
#define BUFFIX( ix , n ) ( ( ix + n + FIRN ) % FIRN )

float sincFunction( float x ) ;

double firCoefficiants ( int increment ,
                        float fc ,
                        float fs ) ;

float clipOutput ( float Y ) ;

int sf_error ( SNDFILE *sf_file_in ) ;

enum errorCode {
    NO_ERROR ,
    NEED_HELP ,
    BAD_ALLOC ,
    BAD_FILE ,
    NOT_MONO ,
    BAD_INPUT
} ;

char* errorText( enum errorCode err ) ;

#endif /* FIRFilter_h */
