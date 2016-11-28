#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include "portaudio.h"

#define NUM_FRAMES 512
#define DELAY_FRAMES 44100
#define DELAY_TIME 5000
// A frame is how many sample periods there are. The total number of samples is
// the product of the number of frames and the number of channels.

enum errorCode {
    NO_ERROR,
    INITIALIZATION_ERROR,
    OPENSTREAM_ERROR,
    STARTSTREAM_ERROR,
    WRITESTREAM_ERROR,
};

char * getErrorText(enum errorCode);

int main(int argc, const char * argv[]) {
    
    enum errorCode status = NO_ERROR;
    
    
    const char * in_filname = "sinesweep.wav";
    
    
    SF_INFO sfinfo;
    PaStream *outputStream;
    
    SNDFILE * sf_file_in = sf_open(in_filname, SFM_READ, &sfinfo);
    PaError err = Pa_Initialize();
    if( err != paNoError ) {
        status = INITIALIZATION_ERROR;
        goto cleanup;
    }
    
    Pa_OpenDefaultStream(&outputStream,
                         0,
                         sfinfo.channels,
                         paFloat32,
                         sfinfo.samplerate,
                         NUM_FRAMES,
                         NULL,
                         NULL
                         );
    
    if( err ) {
        status = OPENSTREAM_ERROR;
        goto cleanup;
    }
    
    float *buffer = calloc(NUM_FRAMES*sfinfo.channels, sizeof(float));
    // Allocate some memory for the buffer.
    
    float *delayBuffer = calloc(DELAY_FRAMES*sfinfo.channels, sizeof(float));
    
    
    sf_count_t numFramesRead = 0;
    // Keep track of how many samples have been read from the file.
    
    Pa_StartStream(outputStream);
    if( err ) {
        status = STARTSTREAM_ERROR;
        goto cleanup;
    }
    
    int x = 0;
    
    do {
        numFramesRead = sf_readf_float(sf_file_in, buffer, NUM_FRAMES);
        for (int n = 0; n < numFramesRead*sfinfo.channels; n++) {
            delayBuffer[x] = buffer[n];
            int index = ( x - DELAY_TIME + DELAY_FRAMES ) % DELAY_FRAMES ;
            buffer[n] += delayBuffer[index];
            x = (x+1)%DELAY_FRAMES;
            }
        Pa_WriteStream(outputStream, buffer, numFramesRead);
        if( err ) {
            status = WRITESTREAM_ERROR;
                goto cleanup;
        }
    } while (numFramesRead > 0);
    
    goto cleanup;
    
    cleanup:
    
    sf_close(sf_file_in);
    Pa_StopStream(outputStream);
    Pa_CloseStream(outputStream);
    Pa_Terminate();
    free(buffer);
    
    return 0;
}

char * getErrorText(enum errorCode err) {
    switch (err) {
        case NO_ERROR:
            return "";
        case INITIALIZATION_ERROR:
            return "PortAudio error: INITILIZATION_ERROR";
        case OPENSTREAM_ERROR:
            return "PortAudio error: OPENSTREAM_ERROR";
        case STARTSTREAM_ERROR:
            return "PortAudio error: STARTSTREAM_ERROR";
        case WRITESTREAM_ERROR:
            return "PortAudio error: WRITESTREAM_ERROR";
        default:
            return "Unknown error";
    }
}

