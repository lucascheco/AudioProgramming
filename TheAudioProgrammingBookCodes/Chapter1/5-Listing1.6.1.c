//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.1 .
//Date: 28/05/2020.

// Find the maximum value nearest the start of the array(buffer).
#include <stdio.h>

int main()
{
    double buffer[1024];
    double *ptr = buffer + 1024;
    double maxValue = 0.0;

    unsigned long pos = 0;

    while (--ptr != buffer)
    {
        // ">=" Is used to find the maximum value nearest the start of the buffer.
        if (*ptr >= maxValue)
        {
            maxValue = *ptr;
            pos = ptr - buffer;
        }
    }

    printf("The maximum sample is %lf, at position %d\n", maxValue, pos);

    return 0;
}