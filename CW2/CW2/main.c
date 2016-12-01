#include <stdlib.h>
#include <math.h>
#include <sndfile.h>

#define NUM_FRAMES 512
// A frame is how many sample periods there are. The total number of samples is
// the product of the number of frames and the number of channels.

#define FIRN 127

// return buffer index
#define BUFFIX(ix,n) ((ix+n+FIRN)%FIRN)

enum errorCode {
    NO_ERROR,
    BAD_ALLOC,
    BAD_FILE,
    NOT_MONO,
    BAD_INPUT
    // Append this list as necessary.
};

char* errorText(enum errorCode err);

float sincFunction(float x);

int main(int argc, const char * argv[]) {
    
    int status = NO_ERROR;
    
    if ( argc != 4 ) {
        if ( argc == 1 ) {
            printf("Please enter three command line arguments in this order:\n"
                   "1) The name of the input file (including the .wav suffix),\n"
                   "2) The name of the output file (including the .wav suffix), and\n"
                   "3) The cut-off frequency of the filter (in Hz).\n");
            goto cleanup;
        }
        else {
            status = BAD_INPUT;
            goto cleanup;
        }
    }

    const char * in_filname = argv[1];
    const char * out_filname = argv[2];
    
    SF_INFO sfinfo;
    
    SNDFILE * sf_file_in = sf_open(in_filname, SFM_READ, &sfinfo);
    
    if (sf_file_in == NULL) {
        status = BAD_FILE;
        goto cleanup;
    }
    
    if (sfinfo.channels > 1) {
        status = NOT_MONO;
        goto cleanup;
    }
    
    SNDFILE * sf_file_out = sf_open(out_filname, SFM_WRITE, &sfinfo);
    
    if (sf_file_out == NULL) {
        status = BAD_FILE;
        goto cleanup;
    }
    
    float fs = sfinfo.samplerate;
    float fc = atof(argv[3]);
    float fcOverfs = (fc/fs);
    
    //Do some error checking
    
    float *buffer = malloc(sizeof(float)*NUM_FRAMES*sfinfo.channels);
    // Allocate some memory for the buffer.
    
    if (buffer == NULL) {
        status = BAD_ALLOC;
        goto cleanup;
    }
    
    //Function for filter coefficiants
    float filterCoefficients[FIRN];
    for (int incriment = 0; incriment < FIRN; incriment++){
        float hammingWindow = (0.54 - 0.46 * cos(2.0 * M_PI * incriment/(FIRN-1.0)));
        float x = (((2.0 * incriment) - (FIRN-1.0)) * fcOverfs);
        float sincComponent = 2.0 * fcOverfs * sincFunction(x);
        filterCoefficients[incriment] = (hammingWindow * sincComponent);
        //printf("%f\n", filterCoefficients[incriment]);
    }
    
    sf_count_t numFramesRead = 0;
    sf_count_t numFramesWritten = 0;
    // Keep track of how many samples have been written to the file.
    
    // process input ----- CORRECT MATHS NEEDS TO GO HERE -----
    
    float X[FIRN];
    unsigned int ix = 0;
    
    
    do {
        numFramesRead = sf_readf_float(sf_file_in, buffer, NUM_FRAMES);
        for (int n = 0; n < numFramesRead*sfinfo.channels; n++) {
            X[BUFFIX(ix,0)] = buffer[n];
            float Y = 0.0;
            for (int incriment = 0; incriment < FIRN; incriment++){
                Y += filterCoefficients[incriment]*X[BUFFIX(ix,  -incriment)];
            }
            
            if (Y > 1.0) {
                Y = 1.0;
            }
            else if (Y < -1.0) {
                Y = -1.0;
            }
            
            buffer[n] = Y;
            ix = BUFFIX(ix, 1);
        }
        numFramesWritten = sf_writef_float(sf_file_out, buffer, numFramesRead);
    }
    while (numFramesRead > 0);
    
cleanup:
    
    sf_close(sf_file_in);
    sf_close(sf_file_out);
    free(buffer);
    
    if (status) {
        printf("%s\n", errorText(status));
        // Print any error text, but only if an error occurred.
    }
    
    return status;
}

//Function for sincFunction
float sincFunction(float x){
    if (x==0){
        return 1;
    }
    else{
        return sin(M_PI * x)/(M_PI * x);
    }
}

char* errorText(enum errorCode err) {
    switch (err) {
        case NO_ERROR:
            return "";
        case BAD_ALLOC:
            return "Unable to allocate memory.";
        case BAD_FILE:
            return "Unable to open file.";
        case BAD_INPUT:
            return "You entered something erroneous.";
        case NOT_MONO:
            return "The input file is not monophonic.";
        default:
            return "An unknown error occurred.";

    }
    
}
