/*
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.2 .
    Date: 28/05/2020.
*/
/* Why we use back-to-front instead of front-to-end ? */
/* Answer: Auto-decrement is faster than Auto-increment, and comparison against zero is faster than comparison with some non-zero value. */

#include <stdio.h>

int main()
{
    float input, output, gain, *samp, *ar;
    unsigned long nsmps, ksmps;
    nsmps = ksmps;

    do
    {
        float sample = *samp++; /* Pointer is incremented not the value, but dereference occurs first(sample = *samp) and than samp++. */
        output = sample - input + (gain * output);
        input = sample;
        *ar++ = output;
    } while (--nsmps);

    return 0;
}