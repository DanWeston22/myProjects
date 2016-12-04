#include <math.h>
#include "FIRFilter.h"
#include <sndfile.h>

//Calculate sinc
float sincFunction( float x ) {
    if ( x == 0 ) {
        return 1 ;
    }
    else {
        return sin( M_PI * x ) / ( M_PI * x ) ;
    }
}

//Calculate filter coefficiants
double firCoefficiants ( int increment ,
                        float fc ,
                        float fs ) {
    float fcOverfs = ( fc / fs ) ;
    float hammingWindow =
    ( 0.54 - 0.46 * cos( 2.0 * M_PI * increment / ( FIRN - 1.0 ) ) ) ;
    float x = ( ( ( 2.0 * increment ) - ( FIRN - 1.0 ) ) * fcOverfs ) ;
    float sincComponent = 2.0 * fcOverfs * sincFunction( x ) ;
    return ( hammingWindow * sincComponent ) ;
}

char* errorText( enum errorCode err ) {
    switch ( err ) {
        case NO_ERROR :
            return "" ;
        case NEED_HELP :
            return "Please enter three command line arguments in this order:\n"
                   "1) The name of the input file"
                   "(including the .wav suffix),\n"
                   "2) The name of the output file"
                   "(including the .wav suffix), and\n"
                   "3) The cut-off frequency of the filter (in Hz)." ;
        case BAD_ALLOC :
            return "Unable to allocate memory." ;
        case BAD_FILE :
            return "Unable to open file." ;
        case NOT_MONO :
            return "The input file is not monophonic." ;
        case BAD_INPUT :
            return "You entered something erroneous." ;
        default :
            return "An unknown error occurred." ;
            
    }
}
