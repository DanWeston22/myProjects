#include <math.h>
#include "FIRFilter.h"
#include <sndfile.h>

static float sincFunction( float x ) ;

static double firCoefficiants ( int increment ,
                        float fc ,
                        float fs ) ;

// return buffer index
#define BUFFIX( ix , n ) ( ( ix + n + FIRN ) % FIRN )

void fir_calculate(fir *f, float fs, float fc) {
    
    for (int increment = 0 ; increment < FIRN ; increment++ ) {
        f->b[ increment ] =
            firCoefficiants( increment , fc , fs ) ;
    }
    
}

float fir_process(fir *f, float x) {
    
    f->x[ BUFFIX( f->index , 0 ) ] = x ;
    float Y = 0.0 ;
    for ( int increment = 0 ;
         increment < FIRN ;
         increment++ )
    {
        Y += f->b[ increment ] *
            f->x[ BUFFIX( f->index , -increment ) ] ;
    }
    
    //Clip output to stop distortion
    if ( Y > 1.0 ) {
        Y = 1.0 ;
    }
    else if ( Y < -1.0 ) {
        Y = -1.0 ;
    }
    
    f->index = BUFFIX( f->index , 1 ) ;
    return Y;
    
}

void fir_processBlock(
    fir *f,
    float * buffer,
    unsigned int length,
    unsigned int step
) {

    for (int n = 0; n < length; n += step) {
        buffer[n] = fir_process(f, buffer[n]);
    }
    
}

//Calculate sinc
static float sincFunction( float x ) {
    if ( x == 0 ) {
        return 1 ;
    }
    else {
        return sin( M_PI * x ) / ( M_PI * x ) ;
    }
}

//Calculate filter coefficiants
static double firCoefficiants ( int increment ,
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
