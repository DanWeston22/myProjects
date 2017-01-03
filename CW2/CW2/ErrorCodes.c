//
//  ErrorCodes.c
//  CW2
//
//  Created by Dan Weston on 03/01/2017.
//  Copyright © 2017 Dan Weston. All rights reserved.
//

#include "ErrorCodes.h"

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
