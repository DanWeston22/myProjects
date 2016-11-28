//
//  Class.hpp
//  Class'
//
//  Created by Dan Weston on 28/11/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#ifndef Class_hpp
#define Class_hpp

#include <stdio.h>

typedef enum {
    BQ_NONE,
    BQ_LOWPASS,
    BQ_HIGHPASS,
    BQ_BANDPASS,
    BQ_NOTCH,
    BQ_PEAK,
    BQ_LOWSHELF,
    BQ_HIGHSHELF,
    BQ_NUM_FILTERS
} bqFilterType;


class biquad {
    
public:
    
    biquad(
           bqFilterType type = BQ_LOWPASS,
           int fs = 44100,
           double fc = 1000,
           double Q = 0.7071,
           double peakGain = 0
    );
    ~biquad(void);
    float process(float);

    
private:
    
    void calculate(void);
    double m_A[BQN];
    double m_B[BQN];
    bqFloat m_X[BQN];
    bqFloat m_Y[BQN];
    unsigned int m_index;
    double m_fs;
    bqFilterType m_type;
    double m_fc;
    double m_Q;
    double m_peakGain;

};

#endif /* Class_hpp */
