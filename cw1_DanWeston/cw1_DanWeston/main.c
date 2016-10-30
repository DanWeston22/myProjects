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

    //'-help' Information.
    if (argc == 2){
        //Check if user inputed '-help'. If they did prints information.
        if (strcmp(argv[1], "-help") == 0){
            printf("Please enter Timing Information and MIDI Note Numbers in the following format:\n<time in milliseconds> <MIDI note number>.\n");
            return 1;
        }
        //If they didn't prints error message and ends program.
        else {
            printf("User input not in a recognised format\n");
            return 1;
        }
    }
    //Arrays to store input data.
    float timingValues[100];
    float midiValues[100];
    
    //Variables for user input.
    float timingInputValue;
    float midiInputValue;
    int numberOfInputLines = 0;
    
    //Count number of input lines.
    for (numberOfInputLines = 0; numberOfInputLines < 100; numberOfInputLines++){
        
        //Gets input from command line.
        char *line = NULL;
        size_t len = 12;
        getline(&line, &len, stdin);
        
        //Variables for splitting up input data.
        char *token = NULL;
        const char space[] = " ";
        char *stopString;
        int inputCharater = 0;

        //Checks input for invalid data (charaters & punctuation) if found ends program.
        for (inputCharater = 0; line[inputCharater] != 0; inputCharater++){
            if ((isalpha(line[inputCharater]) != 0) || (ispunct(line[inputCharater]) && line[inputCharater]!='-')){
                printf ("User input not in a recognised format\n");
                return 2;
            }
        }
        
        //Splits input data and saves first value to timingValue.
        token = strtok(line, space);
        timingInputValue = strtof(token, &stopString);
        
        //Checks for a second value and saves. If there isn't a second value prints error and ends program.
        token = strtok(NULL, space);
        if (token == NULL){
            printf ("User input not in a recognised format\n");
            return 2;
        }
        midiInputValue = strtof(token, &stopString);
        
        //If there is a third value prints error and ends program.
        token = strtok(NULL, space);
        if (token != NULL){
            printf ("User input not in a recognised format\n");
            return 2;
        }
        
        //Saves timing and MIDI input values into the relevant arrays.
        timingValues[numberOfInputLines] = timingInputValue;
        midiValues[numberOfInputLines] = midiInputValue;
        
        //Checks that MIDI value is valid, if not prints error and ends program.
        if (127 < midiInputValue) {
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");
            return 3;
        }
        
        //Checks that the timing values are increasing, if not prints error and ends program.
        if (timingValues[numberOfInputLines-1] > timingValues[numberOfInputLines]){
            printf("The time values need to be non-negative and increasing in value\n");
            return 4;
        }
        
        //If MIDI value is < 0, or if the number of input lines has reached 100 breaks out of loop.
        if (midiInputValue < 0 || numberOfInputLines == 99) {
            break;
        }
    }

    //Loop to cycle through input values and calculate note duration, start time and frequency.
    for (int inputNumber = 1; inputNumber <= numberOfInputLines; ++inputNumber) {
            float duration = (timingValues[inputNumber] - timingValues[inputNumber-1]);
            float frequency = 440.0 * pow(2.0, ((midiValues[inputNumber-1] - 69.0)/12.0));
            float startTime = (timingValues[inputNumber-1]);
            //Declarations
            const int sampleFrequency = 48000.0;
            float omega = (2.0 * M_PI * frequency);
            float phase;
        
            //Loop calculates and prints sample values, and increments phase.
            for (float currentTime; currentTime <= startTime + duration; currentTime += (1000.0/sampleFrequency)){
                float sampleValues = sin(phase);
                printf("%.6f\n", sampleValues);
                phase += (omega/sampleFrequency);
            }
    }
    return 0;
}
