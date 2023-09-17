// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>	// includes sin()
// Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:

extern int arr_size;

void convertToBinaryArray(int inputArray[], int size, int outputArray[], int bits)
{
	for (int i = 0; i < size; i++)
	{
		int num = inputArray[i];
		for (int j = bits - 1; j >= 0; j--)
		{
			outputArray[i * bits + (bits - j - 1)] = (num >> j) & 1;
		}
	}
}

// implementation
float analog_signal_generator(asignal signal, int t)
{
	int A = signal.A;
	int omega = signal.omega;
	int sigma = signal.sigma;

	float result = A * sin(omega * t + sigma);

	return result;
}
void sampler(float *samples, int interval, asignal signal)
{
	int duration = signal.duration;
	int loop_count = (duration / interval) + 1;
	for (int i = 0; i < loop_count; i++)
	{
		samples[i] = analog_signal_generator(signal, i);
	}
}
void quantizer1(float *samples, int *pcmpulses, int levels)
{
	// TODO
}
void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
	int Q = 0;
	int size = arr_size;
	for (int i = 0; i < size; i++)
	{
		Q = floor(((samples[i] - (-A)) / (A - (-A))) * levels);
		pcmpulses[i] = Q;
	}
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	int size = arr_size;
	convertToBinaryArray(pcmpulses, size, dsignal, encoderbits);
}