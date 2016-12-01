#include <iostream>
#include "Class.hpp"

int main(int argc, const char * argv[]) {
    
    // Create filter
    biquad b(biquad::filterType::LOWPASS, 48000);
    
    // Use filter
    b.process(0.1);
    
    b.helloWorld();
    
    biquad::helloWorld();
    
    return 0;
}





