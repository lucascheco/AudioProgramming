//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.7.2 .
//Date: 10/06/2020.

#include <stdio.h>
#include <stdlib.h>

#define SAMPLELEN 1048576

float *sampbuf;

void process_sample(float *samp);

int main()
{
    sampbuf = (float *)malloc(SAMPLELEN * sizeof(float));

    if (sampbuf == NULL)
    {
        puts("Sorry - not that much memory available!\n");
        exit(1);
    }

    process_sample(sampbuf);

    free(sampbuf);

    return 0;
}

void process_sample(float *samp)
{
    /* Do something     */
}
