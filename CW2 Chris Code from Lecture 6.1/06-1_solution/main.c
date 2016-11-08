//
//  main.c
//  05-2_solution
//
//  Created by Christopher Hummersone on 26/10/2016.
//  Copyright © 2016 Christopher Hummersone. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sndfile.h>

#define NUM_FRAMES 512
// A frame is how many sample periods there are. The total number of samples is
// the product of the number of frames and the number of channels.

int main(int argc, const char * argv[]) {
    
    const char * in_filname = "440Hz_44100Hz_16bit_05sec.wav";
    const char * out_filname = "6dB_Reduction.wav";
    
    SF_INFO sfinfo;
    
    SNDFILE * sf_file_in = sf_open(in_filname, SFM_READ, &sfinfo);
    SNDFILE * sf_file_out = sf_open(out_filname, SFM_WRITE, &sfinfo);
    
    //Do some error checking

    float *buffer = malloc(sizeof(float)*NUM_FRAMES*sfinfo.channels);
    // Allocate some memory for the buffer.
    
    sf_count_t numFramesRead = 0;
    sf_count_t numFramesWritten = 0;
    // Keep track of how many samples have been written to the file.
    
     do {
        numFramesRead = sf_readf_float(sf_file_in, buffer, NUM_FRAMES);
         for (int n = 0; n < numFramesRead*sfinfo.channels; n++) {
            buffer[n] /= 2.0;
        }
        numFramesWritten = sf_writef_float(sf_file_out, buffer, numFramesRead);
    }
    while (numFramesRead > 0);
    
    sf_close(sf_file_in);
    sf_close(sf_file_out);
    free(buffer);
    
    return 0;
}
