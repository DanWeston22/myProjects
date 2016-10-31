//
//  main.c
//  Structures
//
//  Created by Dan Weston on 24/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include "Biquad.h"

int main(int argc, const char * argv[]) {
    
    for ( int freqNum = 0 ;
        freqNum < 10 ;
        freqNum++) {
        printf ( "%.2f\n" , biquadFunction( freqNum ) ) ;
    }
    return 0;
}
