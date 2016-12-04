#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include "FIRFilter.h"

int main( int argc , const char * argv[ ] ) {
    
    int status = NO_ERROR ;
    
    if ( argc != 4 ) {
        if ( argc == 1 ) {
            status = NEED_HELP ;
            goto cleanup ;
        }
        else {
            status = BAD_INPUT ;
            goto cleanup ;
        }
    }

    const char * in_filname = argv[ 1 ] ;
    const char * out_filname = argv[ 2 ] ;
    
    //Get input file information
    SF_INFO sfinfo ;
    SNDFILE * sf_file_in = sf_open( in_filname , SFM_READ , &sfinfo ) ;
    
    if ( sf_file_in == NULL ) {
        status = BAD_FILE ;
        goto cleanup ;
    }

    if ( sfinfo.channels > 1 ) {
        status = NOT_MONO ;
        goto cleanup ;
    }
    
    SNDFILE * sf_file_out = sf_open( out_filname ,
                                    SFM_WRITE ,
                                    &sfinfo
                                    ) ;
    
    if ( sf_file_out == NULL ) {
        status = BAD_FILE ;
        goto cleanup ;
    }
    
    //Creates a buffer for file data
    float *buffer = malloc( sizeof( float ) * NUM_FRAMES ) ; // Get rid of this...
    
    if ( buffer == NULL ) {
        status = BAD_ALLOC ;
        goto cleanup ;
    }
    
    //Information for calculating coefficiants
    float fs = sfinfo.samplerate ;
    float fc = atof( argv[ 3 ] ) ;
    
    //Calculate filter coefficiants
    float filterCoefficients[ FIRN ] ;
    for (int increment = 0 ;
        increment < FIRN ;
        increment++ ) {
        filterCoefficients[ increment ] = firCoefficiants( increment ,
                                                          fc ,
                                                          fs
                                                          ) ;
    }
    
    // Keep track of how many samples have been written to the file.
    sf_count_t numFramesRead = 0 ;
    sf_count_t numFramesWritten = 0 ;
    
    // Process input
    float X[ FIRN ] ;
    unsigned int ix = 0 ;
    
    do {
        numFramesRead = sf_readf_float( sf_file_in ,
                                       buffer ,
                                       NUM_FRAMES ) ;
        for ( int n = 0 ;
            n < ( numFramesRead ) ;
            n++ )
        {
            X[ BUFFIX( ix , 0 ) ] = buffer[ n ] ;
            float Y = 0.0 ;
            for ( int increment = 0 ;
                 increment < FIRN ;
                 increment++ )
            {
                Y +=
                filterCoefficients[ increment ]
                * X[ BUFFIX( ix , -increment ) ] ;
            }
            
            if ( Y > 1.0 ) {
                Y = 1.0 ;
            }
            else if ( Y < -1.0 ) {
                Y = -1.0 ;
            }
            
            buffer[n] = Y ;
            ix = BUFFIX( ix , 1 ) ;
        }
        numFramesWritten = sf_writef_float( sf_file_out ,
                                           buffer ,
                                           numFramesRead ) ;
    }
    while ( numFramesRead > 0 ) ;
    
cleanup:
    
    //Close files and free memory
    sf_close( sf_file_in ) ;
    sf_close( sf_file_out ) ;
    free( buffer ) ;
    
    //Print error text, only if an error occurred.
    if ( status ) {
        printf( "%s\n" , errorText( status ) ) ;
    }
    
    return status ;
}
