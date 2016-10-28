//
//  main.c
//  cw1_DanWeston
//
//  Created by Dan Weston on 20/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, const char * argv[]) {

    const int sampleFrequency = 48000.0;                        //Sets sampleFrequency to 48kHz
    float timingValue[100];                                     //Stores up to 100 values in timingValue array
    float midiValue[100];                                       //Stores up to 100 values in timingValue array
    float timingInput;
    float midiInput;
    
    
    if (argc == 2){                                             //Checks to see if user enters '-help'
        if (strcmp(argv[1], "-help") == 0){
            printf("Please enter Timing Information and MIDI Note Numbers in the following format:\n<time in milliseconds> <MIDI note number>\n");                               //Prints format that user should input MIDI & Timing information.
            return 1;
        }
        else {
            printf("User input not in a recognised format\n");
            return 1;
        }
    }
    
    int inputCount = 1.0;                                       //Sets timingCount to zero
    for (inputCount = 1.0; inputCount < 101.0; inputCount++){   //Counts values added to the 1st column of the values array
        int isNumber = scanf("%f", &timingInput);               //Lets user input Timing Information Value
        if (isNumber != 1) {                                    //If scanf didn't find a number to convert then..
            printf ("User input not in a recognised format\n"); //Prints error message when input isn't in the correct format
            break;
        }

        timingValue[inputCount] = timingInput;                  //Sets timingValue array with value [inputCount] timingInput value
                                                                //And converts it to seconds
        scanf("%f", &midiInput);                                //Lets user input MIDI Value
        midiValue[inputCount] = midiInput;                      //Sets midiValue array with value [inputCount] midiInput value
        if (127 < midiInput) {                                                      //Checks if MIDIInput value is > 127
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");    //Error message when MIDI data isn't valid
            return 2;
        }
        if (timingValue[inputCount-1] > timingValue[inputCount]){                   //Checks if time values are increasing
            printf("The time values need to be non-negative and increasing in value\n");    //If not prints error
            return 3;                                                                   //Breaks out of loop and ends programme
        }
        if (midiInput < 0 || inputCount == 100) {        //Checks if MIDIInput value is < 0, or inputCount has readhed 100
            break;
        }

    }
                                                                                        //Or if inputCount has reached 99
            for (int inputNumber = 0; inputNumber <= inputCount; ++inputNumber) {     //For loop to cycle through input values
                float time = (timingValue[inputNumber-2] + timingValue[inputNumber-1]);  //Calculates time to run from timingValues
                float frequency = 440.0 * pow(2.0, ((midiValue[inputNumber-1] - 69.0)/12.0)); //Calculates Frequency from midiValue
                float omega = (2.0 * M_PI * frequency);                                 //Sets omega to equal 2πf
                float phase = 0.0;                                                      //Sets phase to zero
                for (time = timingValue[inputNumber-1]; time < timingValue[inputNumber]; time = (time + (1000.0/sampleFrequency))){                                                                   //For loop for sample value calculation
                    float sineWave = sin(phase);                                        //Calculates the sample values
                    printf("%.6f\n", sineWave);                                         //Prints sample values
                    phase += (omega/sampleFrequency);                                   //Adds 2πf/SR to phase
                }
            }
    return 0;
}

//BUGS

//If less or more than 2 numbers are entered on a line it doesnt give an error message (Try using fgets & sscanf or getline)

//gcc -Wall error!

//Code Complete - Layout

