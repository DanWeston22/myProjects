#ifndef class_hpp
#define class_hpp


#define BQN 3

class biquad {
    
public:
    
    enum class filterType {
        NONE,
        LOWPASS,
        HIGHPASS,
        BANDPASS,
        NOTCH,
        PEAK,
        LOWSHELF,
        HIGHSHELF
    };
    
    biquad(
           filterType type = filterType::LOWPASS,
           int fs = 44100,
           double fc = 1000,
           double Q = 0.7071,
           double peakGain = 0
           );
    ~biquad(void) = default;
    float process(float);
    static void helloWorld(void);
    
private:
    
    void calculate(void);
    
    double m_A[BQN];
    double m_B[BQN];
    float m_X[BQN];
    float m_Y[BQN];
    unsigned int m_index;
    double m_fs;
    filterType m_type;
    double m_fc;
    double m_Q;
    double m_peakGain;
    
};

class example {
public:
    example(double x = 10);
    void sayHello(const biquad& b);
};

#endif /* class_hpp */

