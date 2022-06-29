/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 3, 'hello sine'.
    Date:        29/06/2022
************************************************************************************/
#include <stdio.h>
#include <math.h>

#define SAMPLING_RATE  44100
#define NUM_SECONDS 3
#define NUM_SAMPLES (NUM_SECONDS * SAMPLING_RATE)
#define PI 3.14159265
#define FREQUENCY 440

int main()
{
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        float sample = sin(2 * PI * FREQUENCY * i / SAMPLING_RATE);
        printf("%f\n", sample);
    }

}