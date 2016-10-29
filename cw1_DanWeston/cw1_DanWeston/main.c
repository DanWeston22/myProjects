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
#include <stdlib.h>
#include <ctype.h>

int main(int argc, const char * argv[]) {

    const int sampleFrequency = 48000.0;                        //Sets sampleFrequency to 48kHz
    float timingValues[100];                                     //Stores up to 100 values in timingValue array
    float midiValues[100];                                       //Stores up to 100 values in timingValue array
    float timingInputValue;
    float midiInputValue;
    
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
    
    int numberOfInputLines = 0;                                       //Sets timingCount to zero
    for (numberOfInputLines = 0; numberOfInputLines < 100; numberOfInputLines++){   //Counts values added to the 1st column of the values array
        
        char *line = NULL;
        size_t len = 12;
        getline(&line, &len, stdin);
        char *token = NULL;
        const char delim[] = " ";
        char *stopString;
        
        token = strtok(line, delim);
        
        if (isdigit(*token) == 0){
            printf ("User input not in a recognised format..\n"); //Prints error message when input isn't in the correct format
            return 2;
        }

        timingInputValue = strtof(token, &stopString);
        
        token = strtok(NULL, delim);
        if (token == NULL){
            printf ("User input not in a recognised format\n"); //Prints error message when input isn't in the correct format
            return 2;
        }
        if (isdigit(*token) == 0){
            printf ("User input not in a recognised format..\n"); //Prints error message when input isn't in the correct format
            return 2;
        }
        midiInputValue = strtof(token, &stopString);
        
        token = strtok(NULL, delim);
        if (token != NULL){
            printf ("User input not in a recognised format..\n"); //Prints error message when input isn't in the correct format
            return 2;
        }

        timingValues[numberOfInputLines] = timingInputValue;                  //Sets timingValue array with value [inputCount] timingInput value
        
        midiValues[numberOfInputLines] = midiInputValue;                      //Sets midiValue array with value [inputCount] midiInput value
        
        if (127 < midiInputValue) {                                                      //Checks if MIDIInput value is > 127
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");    //Error message when MIDI data isn't valid
            return 2;
        }
        
        if (timingValues[numberOfInputLines-1] > timingValues[numberOfInputLines]){                   //Checks if time values are increasing
            printf("The time values need to be non-negative and increasing in value\n");    //If not prints error
            return 3;                                                                   //Breaks out of loop and ends programme
        }
        
        if (midiInputValue < 0 || numberOfInputLines == 99) {        //Checks if MIDIInput value is < 0, or inputCount has readhed 100
            break;
        }
    }

    for (int inputNumber = 1; inputNumber <= numberOfInputLines; ++inputNumber) {     //For loop to cycle through input values
            float duration = (timingValues[inputNumber] - timingValues[inputNumber-1]);//Calculates time to run from timingValues
            float frequency = 440.0 * pow(2.0, ((midiValues[inputNumber-1] - 69.0)/12.0)); //Calculates Frequency from midiValue
            float omega = (2.0 * M_PI * frequency);                                 //Sets omega to equal 2πf
            float phase;                                                      //Sets phase to zero
            float startTime = (timingValues[inputNumber-1]);
            
            for (float currentTime; currentTime <= startTime + duration; currentTime += (1000.0/sampleFrequency)){                                                                   //For loop for sample value calculation
                float sampleValues = sin(phase);                                        //Calculates the sample values
                printf("%.6f\n", sampleValues);                                         //Prints sample values
                phase += (omega/sampleFrequency);                                   //Adds 2πf/SR to phase
            }
        }
    return 0;
    }

//BUGS

//If less or more than 2 numbers are entered on a line it doesnt give an error message (Try using fgets & sscanf or getline)

//Code Complete - Layout

