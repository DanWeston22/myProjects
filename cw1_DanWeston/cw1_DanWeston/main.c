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

    const int sampleFrequency = 48000;                          //Sets sampleFrequency to 48kHz
    float timingValue[100];                                     //Stores up to 100 values in timingValue array
    float midiValue[100];                                       //Stores up to 100 values in timingValue array
    
    if (argc == 2){                                             //Checks to see if user enters '-help'
        if (strcmp(argv[1], "-help") == 0){
            printf("Please enter Timing Information and MIDI Note Numbers in the following format:\n<time in milliseconds> <MIDI note number>\n");                               //Prints format that user should input MIDI & Timing information.
            return 1;
        }
        else {
            printf("User input not in a recognised format");
            return 1;
        }
    }
    
    int inputCount = 0.0;                                       //Sets timingCount to zero
    for (inputCount = 0.0; inputCount < 100.0; inputCount++){   //Counts values added to the 1st column of the values array
        float timingInput;
        scanf("%f", &timingInput);                              //Lets user input Timing Information Value
        timingValue[inputCount] = timingInput;             //Sets timingValue array with value [inputCount] timingInput value
                                                                //And converts it to seconds
        float midiInput;
        scanf("%f", &midiInput);                                //Lets user input MIDI Value
        midiValue[inputCount] = midiInput;                      //Sets midiValue array with value [inputCount] midiInput value
    
        if (127 < midiInput) {                                                      //Checks if MIDIInput value is > 127
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");    //Error message when MIDI data isn't valid
            return 2;                                                               //Breaks out of loop and ends programme

        }
    
        else if (midiInput < 0) {                                                   //Checks if MIDIInput value is < 0
            
            for (int inputNumber = 0.0; inputNumber <= inputCount; ++inputNumber) {      //For loop to cycle through input values
                float time = (timingValue[inputNumber-1] + timingValue[inputNumber]);   //Calculates time to run from timingValues
                float frequency = 440 * pow(2, ((midiValue[inputNumber] - 69)/12));     //Calculates Frequency from midiValues
                float sum = timingValue[inputNumber];
                sum += timingValue[inputNumber+1];                                            //Sums values of array timingValue
                for (time = (timingValue[inputNumber]); time < (sum); time++){              //For loop for sample value calculation
                    double sineWave = sin(2 * M_PI * frequency * (time/sampleFrequency));   //Calculates the sample values
                    printf("%.5f\t", sineWave);                                             //Prints sample values
                    printf("%f\n", time/sampleFrequency);                                   //Prints time
                }
            }
             //printf ("The MIDI ‘note on’ message contains data out of bounds\n");      //Error message when MIDI data isn't valid
            //return 2;                                                                 //Breaks out of loop and ends programme
        }
    }
    return 0;
}

