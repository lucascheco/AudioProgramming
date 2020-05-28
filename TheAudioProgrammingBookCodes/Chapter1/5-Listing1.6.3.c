//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.3 .
//Date: 28/05/2020.

#include <stdio.h>

int main()
{

    double buffer[1024];
    double *ptr = buffer + 1024;
    double maxValue = 0.0;

    unsigned long pos = 0;
    int i;

    for (i = 0; i < 1024; i++)
    {
        if (buffer[i] > maxValue)
        {
            maxValue = buffer[i];
            pos = i;
        }
    }
    printf("The maximum sample is %lf, at position %d\n", maxValue, pos);

    return 0;
}