// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
#include <string.h>
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
void decimal_to_binary(int n, int encoderbits, char *binary_str);


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
    for (int i = 1; i < array_size; ++i) {
        samples[i] = analog_signal_generator(signal, interval * (i-1));
    }
}

void quantizer(float *samples, int *pcmpulses, int levels, float A) {
    int array_size = (int)samples[0];
    pcmpulses[0] = array_size;

    for (int i = 1; i < array_size; ++i) {
        int quantization_level = floor((samples[i] + A) * levels / (2 * A));
        pcmpulses[i] = quantization_level;
    }
}

void decimal_to_binary(int n, int encoderbits, char *binary_str) {
    for (int i = encoderbits - 1; i >= 0; --i) {
        binary_str[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    binary_str[encoderbits] = '\0';
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits) {
    int num_elements = pcmpulses[0];
    int binary_str_length = (num_elements - 1) * encoderbits;

    char *binary_str = (char *)malloc(binary_str_length + 1);

    binary_str[0] = '\0';

    for (int i = 1; i < num_elements; ++i) {
        char temp_binary[encoderbits + 1];
        decimal_to_binary(pcmpulses[i], encoderbits, temp_binary);
        strcat(binary_str, temp_binary);
    }

    int count = 0;
    for (int i = 0; i < binary_str_length; ++i) {
        dsignal[i + 1] = binary_str[i] - '0';
        count++;
    }
    dsignal[0] = count;

    free(binary_str);
}
