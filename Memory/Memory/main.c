//
//  main.c
//  Memory
//
//  Created by Dan Weston on 25/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
 
    float sampleFreq = 20.0;
    float incriments = (1.0/sampleFreq);
    float freq = 3.5;
    float freqTwo = 4.0;
    float twoPI = (2.0 * M_PI);
    float time;
    
    for (time = 0.0; time < 1.0; (time += incriments)) {
        
        double sineWave = sin(twoPI * freq * time);
        printf("%5.2f\t", time);
        printf("%f\n", sineWave);
        
    }
    
    for (time = 1.0; time < 2.0; (time += incriments)) {
        
        double sineWave = sin(twoPI * freqTwo * time);
        printf("%5.2f\t", time);
        printf("%f\n", sineWave);
        
    }
    
    return 0;
}
