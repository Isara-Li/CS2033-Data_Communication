// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>   // math lib includes sin()

// user-defined header files
#include "mypcm.h"

// function prototypes
void run(asignal *inputsignal);

int arr_size = 0;

int main()
{
    asignal *inputsignal = (asignal *)malloc(sizeof(asignal));
    run(inputsignal);

    // call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal *inputsignal)
{
    int A, omega, sigma, duration, interval, encoderbits;
    scanf("%d %d %d %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);
    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;

    arr_size = (duration / interval) + 1;

    float *samples = (float *)malloc(sizeof(float) * (duration / interval + 1));
    sampler(samples, interval, *inputsignal);

    int *pcmpulses = (int *)malloc(sizeof(int) * (duration / interval + 1));
    quantizer(samples, pcmpulses, pow(2, encoderbits), A);

    int *dsignal = (int *)malloc(sizeof(int) * (duration / interval + 1) * encoderbits);
    encoder(pcmpulses, dsignal, encoderbits);

    // print each element in dsignal in a single line
    for (int i = 0; i < (duration / interval + 1) * encoderbits; i++)
    {
        printf("%d", dsignal[i]);
    }
}
