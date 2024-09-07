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

    // Store the size of the array as the first function in order to be used in other functions.
    samples[0] = (float)array_size;

    // Start the loop with index 1 since index 0 contains the array size.
    for (int i = 1; i < array_size; ++i) {
        samples[i] = analog_signal_generator(signal, interval * (i-1));
    }
}

void quantizer(float *samples, int *pcmpulses, int levels, float A) {
    int array_size = (int)samples[0];

    // Store the size of the array as the first function in order to be used in other functions
    pcmpulses[0] = array_size;

    for (int i = 1; i < array_size; ++i) {
        int quantization_level = floor((samples[i] + A) * levels / (2 * A));
        pcmpulses[i] = quantization_level;
    }
}

// Helper function to convert decimal values to binary
void decimal_to_binary(int n, int encoderbits, char *binary_str) {
    for (int i = encoderbits - 1; i >= 0; --i) {
        if (n & 1) {
            binary_str[i] = '1';
        } else {
            binary_str[i] = '0';
        }
        n >>= 1;
    }
    binary_str[encoderbits] = '\0';
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits) {
    int num_elements = pcmpulses[0];

    // Store the encoded binary value in a string(char array) initially
    int binary_str_length = (num_elements - 1) * encoderbits;
    char *binary_str = (char *)malloc(binary_str_length + 1);

    binary_str[0] = '\0';

    for (int i = 1; i < num_elements; ++i) {
        char temp_binary[encoderbits + 1];
        decimal_to_binary(pcmpulses[i], encoderbits, temp_binary);
        strcat(binary_str, temp_binary);
    }


    // Convert the char in the char array to int and store in dsignal array
    for (int i = 0; i < binary_str_length; ++i) {
        dsignal[i + 1] = binary_str[i] - '0';
    }


    // Free the memory allocated for the char array
    free(binary_str);
}
