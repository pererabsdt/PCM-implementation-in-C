// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t) {
    float A = signal.A;
    float omega = signal.omega;
    float sigma = signal.sigma;
    float x = A * sin(omega * t + sigma);
    return x;
}


void sampler(float *samples, int interval, asignal signal) {
    int numberOfSamples = signal.duration / interval;
    for (int i = 0; i <= numberOfSamples; ++i) {
        samples[i] = analog_signal_generator(signal, interval * i);
    }
    *samples = 2 * signal.A;
}

void quantizer(float *samples, int *pcmpulses, int levels, float A) {
    while (*samples != 2 * A ) {
        int level = floor((*(samples++) + A) * levels / 2 * A);
        *(pcmpulses++) = level;
    }
    *pcmpulses = 2 * levels;
    
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits) {

}