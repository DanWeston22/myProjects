#ifndef ErrorCodes_h
#define ErrorCodes_h

#include <stdio.h>
#include <sndfile.h>

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

#endif /* ErrorCodes_h */
