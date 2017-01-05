//
//  main.c
//  DelayLine
//
//  Created by Dan Weston on 05/01/2017.
//  Copyright © 2017 Dan Weston. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "sndfile.h"
#include "delayLine.h"

enum errorCode {
    NO_ERROR ,
    NEED_HELP ,
    BAD_ALLOC ,
    BAD_FILE ,
    NOT_MONO ,
    BAD_INPUT
} ;

char* errorText(enum errorCode err);


int main( int argc , const char * argv[ ] ) {
    
    int status = NO_ERROR ;
    
    if ( argc != 5 ) {
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
    float *buffer = malloc( sizeof( float ) * NUM_FRAMES * sfinfo.channels ) ;
    
    if ( buffer == NULL ) {
        status = BAD_ALLOC ;
        goto cleanup ;
    }
    
    //Information for calculating coefficiants
    /*float fs = sfinfo.samplerate ;*/
    float delayTime = atof( argv[ 3 ] ) ;
    float feedback = atof ( argv [ 4 ] ) ;
    
    // Keep track of how many samples have been written to the file.
    sf_count_t numFramesRead = 0 ;
    sf_count_t numFramesWritten = 0 ;
    
    delay *delayLine = calloc(sfinfo.channels, sizeof(delay));
    
    // Process input
    do {
        numFramesRead = sf_readf_float( sf_file_in ,
                                       buffer ,
                                       NUM_FRAMES ) ;
        for (int c = 0; c < sfinfo.channels; c++) {
            delay_processBlock(delayLine, buffer+c, delayTime, feedback,
                             (unsigned int)numFramesRead*sfinfo.channels,
                             sfinfo.channels);
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

