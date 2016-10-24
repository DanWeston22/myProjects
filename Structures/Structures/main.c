//
//  main.c
//  Structures
//
//  Created by Dan Weston on 24/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <complex.h>

int main(int argc, const char * argv[]) {

    //Defines Values of b0, b1, b2, a0, a1, a2
    
    int b0 = 1;
    int b1 = -2;
    int b2 = 1;
    int a0 = 1;
    double a1 = -0.2;
    double a2 = 0.17;
    
    //Create array for required values for Frequency
    float freq[] = {50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 20000};
    double PI2 = (2 * M_PI); //Does equation (j * 2 * Pi)
    
    float transferFunction;
    int a;
    for (a = 0; a < 10; a++) { //For values of Freq (0-10) does following code..
        double T = (1.0/44100.0); //States T as 1/sampling freq
        float complex z = cexp(freq[a] * PI2 * T); //States z as e^(freq * jPI2 * T)
        float complex topLine = (b0 + (b1 * cpow(z, -1)) + (b2 * cpow(z, -2)));//Maths..
        float complex bottomLine = (a0 + (a1 * cpow(z, -1)) + (a2 * cpow(z, -2))); //More Maths..
        transferFunction = cabs(topLine / bottomLine);//Putting Maths Together..
        printf ("%5.0f\t", freq[a]);//Print Freq
        printf ("%.2f\n", transferFunction);//Print Transfer Function
    }
    return 0;
}
