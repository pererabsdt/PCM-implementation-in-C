// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main() {
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    free(inputsignal);
    return 0;
}

void run(asignal* inputsignal) {
    // Variables to store the inputs
    float A, omega, sigma;
    int duration, interval, encoderbits;

    // Get inputs from user
    scanf("%f %f %f %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);

    // Assign values to the fields of the inputsignal instance of the asignal struct
    inputsignal->A = A;
    inputsignal->sigma = sigma;
    inputsignal->omega = omega;
    inputsignal->duration = duration;

    int levels = pow(2, encoderbits);
    int array_size = (duration / interval) + 2;

    float sampleArray[array_size];
    sampler(sampleArray, interval, *inputsignal);

    int pcmpulsesArray[array_size];
    quantizer(sampleArray, pcmpulsesArray, levels, A);

    int number_of_bits = encoderbits * (array_size - 1);
    int dsignalArray[number_of_bits + 1];
    encoder(pcmpulsesArray, dsignalArray, encoderbits);

    for (int i = 0; i < number_of_bits; ++i) {
        printf("%d", dsignalArray[i]);
    }
}





