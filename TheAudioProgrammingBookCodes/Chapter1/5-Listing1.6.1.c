/*
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.1 .
    Date: 28/05/2020.
*/

/* Find the maximum value nearest the start of the array(buffer). */
#include <stdio.h>

int main()
{
    double buffer[1024];
    double *ptr = buffer + 1024;
    double maxValue = 0.0;

    unsigned long pos = 0;

    /* Addresses are compared, but pre-decrement is applied first. 'ptr' is compared with the start of the array. */
    while (--ptr != buffer)
    {
        /* ">=" Is used to find the maximum value "nearest" the start of the buffer. 
            If we used just ">" we would find just the maximum value.
        */
        if (*ptr >= maxValue)
        {
            maxValue = *ptr;

            /* Since adresses are big integers, we do this calulation
               rather than setting pos to ptr.*/
            pos = ptr - buffer;
        }
    }

    printf("The maximum sample is %lf, at position %d\n", maxValue, pos);

    return 0;
}