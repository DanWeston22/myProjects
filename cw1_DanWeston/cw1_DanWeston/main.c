//
//  main.c
//  cw1_DanWeston
//
//  Created by Dan Weston on 20/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {

    //float samples[48000]; //Array of 48000 samples
    
    float timingValue[100];                                     //Stores up to 100 values in timingValue array
    float midiValue[100];                                       //Stores up to 100 values in timingValue array
    
    int inputCount = 0;                                         //Sets timingCount to zero
    for (inputCount = 0; inputCount < 100; inputCount++){       //Counts values added to the 1st column of the values array
        float timingInput;
        scanf("%f", &timingInput);
        timingValue[inputCount] = timingInput;                  //Sets timingValue array with value [inputCount] timingInput value
        
        float midiInput;
        scanf("%f", &midiInput);
        midiValue[inputCount] = midiInput;                      //Sets midiValue array with value [inputCount] midiInput value
    }
    
    
    
    printf ("User input not in a recognised format\n");         //Prints error message when input isn't in the correct format
    
    return 0;
}


//Calculates frequency (Hz) of MIDI values (0 - 127)

//float midi[127]; //Array of 127 MIDI values
//int a = 440; // a is 440 hz
//for (int x = 0; x < 127; ++x)
//{
    //midi[x] = (a / 32) * (2 ^ ((x - 9) / 12)); // Calculates frequency of each MIDI value
//}

/////////////////////////////////////////////////////////

//Error for invalid MIDI value

//if (-128 < midiValue < 127) { //Checks that MIDI value is valid
    //break;
//}
//else {
    //printf ("The MIDI ‘note on’ message contains data out of bounds\n"); //Error message when MIDI data isn't valid
//}

/////////////////////////////////////////////////////////

//-help information

//if (timingInformation == '-help'){
    //printf ("Please enter Timing Information and MIDI Note Numbers in the following format:\n<time in milliseconds> <MIDI note number>\n"); //Prints format that user should input MIDI & Timing information.
//}
