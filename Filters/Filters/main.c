#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include "firFilter.h"

#define NUM_FRAMES 512
// A frame is how many sample periods there are. The total number of samples is
// the product of the number of frames and the number of channels.

int main(int argc, const char * argv[]) {
    
    const char * in_filname = "AveVerum.wav";
    const char * out_filname = "BiquadFiltered.wav";
    
    SF_INFO sfinfo;
    
    SNDFILE * sf_file_in = sf_open(in_filname, SFM_READ, &sfinfo);
    SNDFILE * sf_file_out = sf_open(out_filname, SFM_WRITE, &sfinfo);
    
    fir *b = fir_create(
                              sfinfo.samplerate,
                              1000
                              );
    
    
    //Do some error checking
    
    float *buffer = malloc(sizeof(float)*NUM_FRAMES*sfinfo.channels);
    // Allocate some memory for the buffer.
    
    sf_count_t numFramesRead = 0;
    sf_count_t numFramesWritten = 0;
    // Keep track of how many samples have been written to the file.
    
    do {
        numFramesRead = sf_readf_float(sf_file_in, buffer, NUM_FRAMES);
        for (int n = 0; n < numFramesRead*sfinfo.channels; n++) {
            buffer[n] = fir_process(b, buffer[n]);
        }
        numFramesWritten = sf_writef_float(sf_file_out, buffer, numFramesRead);
    }
    while (numFramesRead > 0);
    
    fir_destroy(b);
    sf_close(sf_file_in);
    sf_close(sf_file_out);
    free(buffer);
    
    return 0;
}

