//
//  delayLine.h
//  DelayLine
//
//  Created by Dan Weston on 05/01/2017.
//  Copyright © 2017 Dan Weston. All rights reserved.
//

#ifndef delayLine_h
#define delayLine_h

#include <stdio.h>
#define NUM_FRAMES 512
#define samples 2000 //Filter Order Number + 1.

typedef struct delay_s {
    float x[samples];
    float d[samples];
    unsigned int index;
} delay;

float delay_process(delay *d, float x, int delayTime, float feedback );

void delay_processBlock(delay *f, float * buffer, int delayTime,
                        float feedback, unsigned int length, unsigned int step);

#endif /* delayLine_h */
