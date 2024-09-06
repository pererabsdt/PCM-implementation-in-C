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

    call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal* inputsignal) {

}


