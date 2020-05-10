//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", about casting.
//Date: 07/06/2020.

#include <stdio.h>

int main()
{
    double fracsamp;
    short samp;

    fracsamp = 0.5;
    samp = (short)(fracsamp * 32767);

    
    return 0;
}