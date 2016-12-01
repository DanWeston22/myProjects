#include "Class.hpp"
#include <cmath>
#include <iostream>

// return buffer index
#define BUFFIX(n,k) ((n+k+BQN)%BQN)

biquad::biquad(
               filterType type,
               int fs,
               double fc,
               double Q,
               double peakGain
               ) :
m_index(0),
m_fs(fs),
m_type(type),
m_fc(fc),
m_Q(Q),
m_peakGain(peakGain) {
    calculate();
}

float biquad::process(float input) {
    
    double *A = m_A;
    double *B = m_B;
    float *X = m_X;
    float *Y = m_Y;
    unsigned int n = m_index;
    
    // put input on to buffer
    X[BUFFIX(n,0)] = input;
    
    // process input
    Y[BUFFIX(n,0)] =
    B[0]*X[BUFFIX(n,  0)] +
    B[1]*X[BUFFIX(n, -1)] +
    B[2]*X[BUFFIX(n, -2)] -
    A[1]*Y[BUFFIX(n, -1)] -
    A[2]*Y[BUFFIX(n, -2)];
    
    // write output
    float output = Y[BUFFIX(n, 0)];
    
    // step through buffer
    m_index = BUFFIX(n, 1);
    
    return output;
    
}

void biquad::calculate(void) {
    // shorten names
    double *A = m_A;
    double *B = m_B;
    double Q = m_Q;
    double fs = m_fs;
    double fc = m_fc;
    double peakGain = m_peakGain;
    
    double AA  = pow(10.0,peakGain/40.0);
    double w0 = 2.0*M_PI*fc/fs;
    double alpha = sin(w0)/(2.0*Q);
    
    // source : http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
    
    switch (m_type) {
            
        case filterType::LOWPASS:
            B[0] = (1.0 - cos(w0))/2.0;
            B[1] = 1.0 - cos(w0);
            B[2] = (1.0 - cos(w0))/2.0;
            A[0] = 1 + alpha;
            A[1] = -2.0*cos(w0);
            A[2] = 1.0 - alpha;
            break;
        case filterType::HIGHPASS:
            B[0] = (1.0 + cos(w0))/2.0;
            B[1] = -(1.0 + cos(w0));
            B[2] = (1.0 + cos(w0))/2.0;
            A[0] = 1.0 + alpha;
            A[1] = -2.0*cos(w0);
            A[2] = 1.0 - alpha;
            break;
        case filterType::BANDPASS: // (constant 0 dB peak gain)
            B[0] = alpha;
            B[1] = 0.0;
            B[2] = -alpha;
            A[0] = 1.0 + alpha;
            A[1] = -2.0*cos(w0);
            A[2] = 1.0 - alpha;
            break;
        case filterType::NOTCH:
            B[0] = 1.0;
            B[1] = -2.0*cos(w0);
            B[2] = 1.0;
            A[0] = 1.0 + alpha;
            A[1] = -2.0*cos(w0);
            A[2] = 1.0 - alpha;
            break;
        case filterType::PEAK:
            B[0] = 1.0 + alpha*AA;
            B[1] = -2.0*cos(w0);
            B[2] = 1.0 - alpha*AA;
            A[0] = 1.0 + alpha/AA;
            A[1] = -2.0*cos(w0);
            A[2] = 1.0 - alpha/AA;
            break;
        case filterType::LOWSHELF:
            B[0] = AA*( (AA+1.0) - (AA-1.0)*cos(w0) + 2.0*sqrt(AA)*alpha );
            B[1] = 2.0*AA*( (AA-1) - (AA+1.0)*cos(w0) );
            B[2] = AA*( (AA+1.0) - (AA-1.0)*cos(w0) - 2.0*sqrt(AA)*alpha );
            A[0] = (AA+1.0) + (AA-1.0)*cos(w0) + 2.0*sqrt(AA)*alpha;
            A[1] = -2.0*( (AA-1.0) + (AA+1.0)*cos(w0) );
            A[2] = (AA+1.0) + (AA-1.0)*cos(w0) - 2.0*sqrt(AA)*alpha;
            break;
        case filterType::HIGHSHELF:
            B[0] = AA*( (AA+1.0) + (AA-1.0)*cos(w0) + 2.0*sqrt(AA)*alpha );
            B[1] = -2.0*AA*( (AA-1.0) + (AA+1.0)*cos(w0) );
            B[2] = AA*( (AA+1.0) + (AA-1.0)*cos(w0) - 2.0*sqrt(AA)*alpha );
            A[0] = (AA+1.0) - (AA-1.0)*cos(w0) + 2.0*sqrt(AA)*alpha;
            A[1] = 2.0*( (AA-1.0) - (AA+1.0)*cos(w0) );
            A[2] = (AA+1.0) - (AA-1.0)*cos(w0) - 2.0*sqrt(AA)*alpha;
            break;
        case filterType::NONE:
        default:
            B[0] = 1.0;
            B[1] = 0.0;
            B[2] = 0.0;
            A[0] = 1.0;
            A[1] = 0.0;
            A[2] = 0.0;
    }
    
    // normalize
    double norm = A[0];
    for (int i = 0; i < BQN; i++) {
        A[i] /= norm;
        B[i] /= norm;
    }
    
}

void biquad::helloWorld(void) {
    std::cout << "Hello World!\n";
}

void example::sayHello(const biquad& b) {
    return b.helloWorld();
}
