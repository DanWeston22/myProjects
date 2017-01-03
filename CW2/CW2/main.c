#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include "FIRFilter.h"
#include "ErrorCodes.h"

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

    /*if ( sfinfo.channels > 1 ) {
        status = NOT_MONO ;
        goto cleanup ;
    }*/
    
    SNDFILE * sf_file_out = sf_open( out_filname ,
                                    SFM_WRITE ,
                                    &sfinfo
                                    ) ;
    
    if ( sf_file_out == NULL ) {
        status = BAD_FILE ;
        goto cleanup ;
    }
    
    //Creates a buffer for file data
    float *buffer = malloc( sizeof( float ) * NUM_FRAMES * sfinfo.channels ) ;
    
    if ( buffer == NULL ) {
        status = BAD_ALLOC ;
        goto cleanup ;
    }
    
    //Information for calculating coefficiants
    float fs = sfinfo.samplerate ;
    float fc = atof( argv[ 3 ] ) ;
    
    // Keep track of how many samples have been written to the file.
    sf_count_t numFramesRead = 0 ;
    sf_count_t numFramesWritten = 0 ;
    
    fir *filters = calloc(sfinfo.channels, sizeof(fir));
    for (int c = 0 ; c < sfinfo.channels; c++ ) {
        fir_calculate(&filters[c], fs, fc);
    }
    
    // Process input
    do {
        numFramesRead = sf_readf_float( sf_file_in ,
                                       buffer ,
                                       NUM_FRAMES ) ;
        for (int c = 0; c < sfinfo.channels; c++) {
            fir_processBlock(filters+c, buffer+c, (unsigned int)numFramesRead*sfinfo.channels, sfinfo.channels);
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
