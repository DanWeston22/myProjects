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

int error() ;

int main( int argc , const char * argv[ ] ) {

    //Checks how many arguents were passed in command line.
    if ( argc == 2 ) {
        //Checks second argument for '-help'. If found prints information.
        if ( strcmp( argv[ 1 ] , "-help" ) == 0 ) {
            printf( "Please enter Timing Information and MIDI Note Numbers in the following format:\n"
                "<time in milliseconds> <MIDI note number>\n"
                "The Timing information should be non-negative, and if multiple timing values are passed they should be increasing in value.\n"
                "The MIDI Note Numbers should be in the range of 0-127.\n"
                "To run the program the last MIDI value entered should be negative (e.g '-1').\n"
                "A maximum of 100 note values can be entered.\n" ) ;
            return 0 ;
        }
    }
    //If more than 2 arguments, or argv[ 1 ] isn't '-help' ends program.
    if ( ( argc > 2 ) ||
        ( ( argc == 2 ) &&
        ( strcmp ( argv[ 1 ] , "-help" ) != 0 ) ) ) {
            return 1 ;
        }

    //Arrays to store input data.
    float timingValues[ 100 ] ;
    float midiValues[ 100 ] ;
    
    //Variables for user input.
    float timingInputValue ;
    float midiInputValue ;
    int numberOfInputLines = 0 ;
    
    //Initialisation for output loop
    float phase = 0.0 ;
    const int sampleFrequency = 48000 ;
    
    //Count number of input lines.
    for ( numberOfInputLines = 0 ;
        numberOfInputLines < 100 ;
        numberOfInputLines++ ) {
        
        //Gets input from command line and strips newline character replacing it with ' '.
        char *line = NULL ;
        size_t len = 12 ;
        getline( &line , &len , stdin ) ;
        char blank = ' ';
        char* firstNewLine = strstr( line , "\n" ) ;
        *firstNewLine = blank ;
        
        //Variables for splitting up input data.
        char *token = NULL ;
        const char space[] = " " ;
        char *stopString ;
        int inputCharater = 0 ;
        
        //Checks input for invalid data (charaters & punctuation) if found ends program.
        for ( inputCharater = 0 ;
            line[ inputCharater ] != 0 ;
            inputCharater++ ) {
            
            if ( ( isalpha ( line[ inputCharater ] ) != 0 ) ||
                ( ispunct ( line[ inputCharater ] ) &&
                line[ inputCharater ] != '-' ) ||
                ( ( line[ inputCharater ] == '-' ) &&
                isdigit( line[ inputCharater + 1 ] ) == 0 ) ) {
                error() ;
                return 1 ;
            }
        }
        
        //Splits input data and saves 1st value to timingValue, if there isn't a 1st value prints error and ends program.
        token = strtok( line , space ) ;
        if ( token == NULL ) {
            error() ;
            return 1 ;
        }
        timingInputValue = strtof( token , &stopString ) ;
        
        //Checks for a 2nd value and saves. If there isn't a 2nd value prints error and ends program.
        token = strtok( NULL , space ) ;
        if ( token == NULL ) {
            error() ;
            return 1 ;
        }
        midiInputValue = strtof( token , &stopString ) ;
        
        //If there is a 3rd value prints error and ends program.
        token = strtok( NULL , space ) ;
        if ( token != NULL ) {
            error() ;
            return 1 ;
        }
        
        //Saves timing and MIDI input values into the relevant arrays.
        timingValues[ numberOfInputLines ] = timingInputValue ;
        midiValues[ numberOfInputLines ] = midiInputValue ;
        
        //Checks that MIDI value is valid, if not prints error and ends program.
        if ( 127 < midiInputValue ) {
            printf ( "The MIDI ‘note on’ message contains data out of bounds.\n" );
            return 2 ;
        }
        
        //Checks that the timing values are increasing, and non negative if not prints error and ends program.
        if ( ( timingValues[ numberOfInputLines ] < 0 ) ||
            ( timingValues[ numberOfInputLines - 1 ] >= timingValues[ numberOfInputLines ] &&
            numberOfInputLines != 0 ) ) {
            printf( "The time values need to be non-negative and increasing in value.\n" ) ;
            return 3 ;
        }
        
        //If MIDI value is < 0, or if the number of input lines has reached 100 breaks out of loop.
        if ( ( midiInputValue < 0 ||
            numberOfInputLines == 99 ) ) {
            break ;
        }
    }

    //Loop to cycle through input values and calculate note duration, start time, frequency and omega.
    for ( int inputNumber = 1 ;
        inputNumber <= numberOfInputLines ;
        ++inputNumber ) {
        float duration = ( timingValues[ inputNumber ] - timingValues[ inputNumber - 1 ] ) ;
        float frequency = 440.0 * pow( 2.0 , ( ( midiValues[ inputNumber - 1 ] - 69.0 ) / 12.0 ) ) ;
        float startTime = ( timingValues[ inputNumber - 1 ] ) ;
        float omega = ( 2.0 * M_PI * frequency ) ;
        
            //Loop calculates and prints sample values, and increments phase.
            for ( float currentTime = startTime ;
                currentTime <= startTime + duration ;
                currentTime += ( 1000.0 / sampleFrequency ) ){
                float sampleValues = sin( phase ) ;
                printf( "%.6f\n" , sampleValues ) ;
                phase += ( omega / sampleFrequency ) ;
            }
    }
    return 0 ;
}

//Function to print error message
int error() {
    printf ( "User input not in a recognised format.\n" ) ;
    return 0 ;
}
