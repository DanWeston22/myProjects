//
//  main.c
//  cw1_DanWeston
//
//  Created by Dan Weston on 20/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {

    const int sampleFrequency = 48000;
    float timingValue[100];                                     //Stores up to 100 values in timingValue array
    float midiValue[100];                                       //Stores up to 100 values in timingValue array
    
    int inputCount = 0.0;                                       //Sets timingCount to zero
    for (inputCount = 0.0; inputCount < 100.0; inputCount++){   //Counts values added to the 1st column of the values array
        float timingInput;
        int isNumber = scanf("%f", &timingInput);               //Lets user input Timing Information Value
        if (isNumber != 1) {                                    //If scanf didn't find a number to convert then..
            printf ("User input not in a recognised format\n"); //Prints error message when input isn't in the correct format
            return 1;
            
            
            //Currently just checks if input is number.. Needs to be fixed for if the 2 input values arent on single line! Try using fgets and sscanf
            
        }
        else {
        timingValue[inputCount] = timingInput/1000;             //Sets timingValue array with value [inputCount] timingInput value
        }                                                       //And converts it to seconds
        
        float midiInput;
        scanf("%f", &midiInput);                                //Lets user input MIDI Value
        midiValue[inputCount] = midiInput;                      //Sets midiValue array with value [inputCount] midiInput value
        
        if (127 < midiInput) {                                                      //Checks if MIDIInput value is > 127
            printf ("The MIDI ‘note on’ message contains data out of bounds\n");    //Error message when MIDI data isn't valid
            return 2;                                                               //Breaks out of loop and ends programme
        
            //Needs to be adapted for - values triggering the start of the sample values
            
        }
        else if (midiInput < 0) {                                                   //Checks if MIDIInput value is < 0
            
            for (int inputNumber = 0.0; inputNumber < 100.0; ++inputNumber) {           //For loop to cycle through input values
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


//Calculates frequency (Hz) of MIDI values (0 - 127)

//float midi[127]; //Array of 127 MIDI values
//int a = 440; // a is 440 hz
//for (int x = 0; x < 127; ++x)
//{
    //midi[x] = (a / 32) * (2 ^ ((x - 9) / 12)); // Calculates frequency of each MIDI value
//}

/////////////////////////////////////////////////////////

//Error for inccorect input format



/////////////////////////////////////////////////////////

//-help information

//if (timingInformation == '-help'){
    //printf ("Please enter Timing Information and MIDI Note Numbers in the following format:\n<time in milliseconds> <MIDI note number>\n"); //Prints format that user should input MIDI & Timing information.
    //break;
//}

//char checkForHelp[5] = "-help";
//if (strcmp(timingInput, checkForHelp) ==0){
    //}


