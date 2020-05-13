//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", about casting.
//Date: 09/05/2020.

#include <stdio.h>

int main()
{
    double fracsamp;
    short samp;

    fracsamp = 0.5;
    samp = (short)(fracsamp * 32767);

    printf("%i\n", samp);
    return 0;
}

/*
    OUTPUT SAMPLE:
        16383
*/