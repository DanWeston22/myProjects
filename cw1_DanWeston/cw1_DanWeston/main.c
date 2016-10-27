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

    const int sampleFrequency = 48000.0;                          //Sets sampleFrequency to 48kHz
    float timingValue[100];                                     //Stores up to 100 values in timingValue array
    float midiValue[100];                                       //Stores up to 100 values in timingValue array
    
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
    
    int inputCount = 0.0;                                       //Sets timingCount to zero
    for (inputCount = 0.0; inputCount < 100.0; inputCount++){   //Counts values added to the 1st column of the values array
        float timingInput;
        int isNumber = scanf("%f", &timingInput);               //Lets user input Timing Information Value
        if (isNumber != 1) {                                    //If scanf didn't find a number to convert then..
            printf ("User input not in a recognised format\n"); //Prints error message when input isn't in the correct format
            break;
        }

        timingValue[inputCount] = timingInput;                  //Sets timingValue array with value [inputCount] timingInput value
                                                                //And converts it to seconds
        float midiInput;
        scanf("%f", &midiInput);                                //Lets user input MIDI Value
        midiValue[inputCount] = midiInput;                      //Sets midiValue array with value [inputCount] midiInput value
        
        
        if (127 < midiInput) {                                                      //Checks if MIDIInput value is > 127
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");    //Error message when MIDI data isn't valid
            return 2;                                                               //Breaks out of loop and ends programme
        }
        
        if (timingValue[inputCount-1] > timingValue[inputCount]){                           //Checks if time values are increasing
            printf("The time values need to be non-negative and increasing in value\n");    //If not prints error
            return 3;
        }
    
        else if (midiInput < 0 || inputCount == 99) {                                   //Checks if MIDIInput value is < 0
                                                                                        //Or if inputCount has reached 99
            for (int inputNumber = 0.0; inputNumber <= inputCount; ++inputNumber) {     //For loop to cycle through input values
                float time = (timingValue[inputNumber-1] + timingValue[inputNumber]);   //Calculates time to run from timingValues
                float frequency = 440.0 * pow(2.0, ((midiValue[inputNumber] - 69.0)/12.0)); //Calculates Frequency from midiValue
                float omega = (2.0 * M_PI * frequency);                                 //Sets omega to equal 2πf
                float phase = 0.0;                                                      //Sets phase to zero
                for (time = timingValue[inputNumber]; time < timingValue[inputNumber+1]; time = (time + (1000.0/sampleFrequency))){                                                                   //For loop for sample value calculation
                    float sineWave = sin(phase);                                        //Calculates the sample values
                    printf("%.6f\n", sineWave);                                         //Prints sample values
                    phase += (omega/sampleFrequency);                                   //Adds 2πf/SR to phase
                }
            }
        }
    }
    return 0;
}

