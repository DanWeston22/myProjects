//
//  delayLine.c
//  DelayLine
//
//  Created by Dan Weston on 05/01/2017.
//  Copyright © 2017 Dan Weston. All rights reserved.
//

#include "delayLine.h"

// return buffer index
#define BUFFIX( ix , n ) ( ( ix + n + samples ) % samples )

float delay_process(delay *d, float x, int delayTime, float feedback) {
    
    d->x[ BUFFIX( d->index , 0 ) ] = x ;
    float delayOut = 0.0 ;
    float feedbackLoop = 0.0 ;
    for ( int increment = 0 ;
         increment < samples ;
         increment++ )
    {
        delayOut =
        d->x[ BUFFIX( d->index , -increment ) + delayTime ] ;
        
        feedbackLoop = d->x[ BUFFIX( d->index , -increment ) ] +
        ( ( feedback / 100.0 ) * delayOut ) ;
    }
    
    //Clip output to stop distortion
    if ( feedbackLoop > 1.0 ) {
        feedbackLoop = 1.0 ;
    }
    else if ( feedbackLoop < -1.0 ) {
        feedbackLoop = -1.0 ;
    }
    
    d->index = BUFFIX( d->index , 1 ) ;
    return feedbackLoop;

}

void delay_processBlock(
                      delay *d,
                      float * buffer,
                      int delayTime,
                      float feedback,
                      unsigned int length,
                      unsigned int step
                      ) {
    
    for (int n = 0; n < length; n += step) {
        buffer[n] = delay_process( d, buffer[n], delayTime, feedback );
    }
    
}
