// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
#include <string.h>
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int decimal_to_binary(int n);


// implementation
float analog_signal_generator(asignal signal, int t) {
    float A = signal.A;
    float omega = signal.omega;
    float sigma = signal.sigma;
    float x = A * sin(omega * t + sigma);
    return x;
}


void sampler(float *samples, int interval, asignal signal) {
    int number_of_samples = signal.duration / interval;
    int array_size = number_of_samples + 2;
    samples[0] = (float)array_size;
    for (int i = 1; i <= number_of_samples + 1; ++i) {
        samples[i] = analog_signal_generator(signal, interval * i);
    }
}

void quantizer(float *samples, int *pcmpulses, int levels, float A) {
    while (*samples != 2 * A ) {
        int level = floor((*(samples++) + A) * levels / (2 * A));
        *(pcmpulses++) = level;
    }
//    *pcmpulses = 2 * levels;

}

void encoder(int *pcmpulses, int *dsignal, int encoderbits) {
    int levels = pow(2, encoderbits);
    while (*pcmpulses != 2 * levels) {
        int value = *pcmpulses;
        int binary_value = decimal_to_binary(value);
        *(dsignal++) = binary_value;
        pcmpulses++;
    }

}

int decimal_to_binary(int n) {
    char binaryStr[32];
    int i = 0;

    if (n == 0) {
        return 0;
    }

    while (n > 0) {
        binaryStr[i] = (n % 2) + '0';
        n = n / 2;
        i++;
    }
    binaryStr[i] = '\0';

    // Reverse the string because binary digits were added in reverse order
    int len = strlen(binaryStr);
    for (int j = 0; j < len / 2; j++) {
        char temp = binaryStr[j];
        binaryStr[j] = binaryStr[len - j - 1];
        binaryStr[len - j - 1] = temp;
    }

    int binaryInt = 0;
    for (int k = 0; k < len; k++) {
        binaryInt = binaryInt * 10 + (binaryStr[k] - '0');
    }

    return binaryInt;
}