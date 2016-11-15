#include <stdio.h>

//Outside main so it can be used by functions
struct gps {
    double lat;
    double lng;
};

struct complex {
    double real;
    double imag;
}; //complexNumbers

int main(int argc, const char * argv[]) {
   
    //There are many data types (double, float, char etc)
    double x;
    float y;
    //struct is also a data type
    //struct is a way of collating varioables of known typesf
    struct {
        double x;
        float y;
        char * str;
    } bob;
    //bob is a structure containing known variables (members) x, y and str
    
    struct complex complexNumbers; //Can also be initialised like this instead of after curly braces.
    
    struct gps coordinates;
    
    struct note {
        double pitch;
        double velocity;
        double buffer[3];
        struct {double bob;} structure;
        //struct note me; --- This isnt allowed
        //These are all allowed, however you cant have a structure of the same type within a structure
        struct note * me;
        //You can however have a pointer to a structure
    } music;
    
    scanf("%lf &lf", &music.pitch, &music.velocity);
    
    typedef double frequency;
    //Creates an alias 'frequency' for the data type double
    
    frequency one = 2.0;
    //here one is created with a type frequency which is a double..
    
    typedef struct note note;
    
}

void doStuff(struct gps x) {
    //x. means this is a structure
    //lat is the data type lat from the gps struct
    x.lat = 0.0;
    x.lng = 1.0;
    //x.othermembers
}

//Now using pointers
void moreStuff(struct complex * x) {
    (*x).real = 0.0;
    x->imag = 1.0;
    //Using -> is the same as dereferencing (*x)
}
