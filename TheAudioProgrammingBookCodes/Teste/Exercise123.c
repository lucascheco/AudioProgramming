//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", about casting.
//Date: 09/06/2020.

#include <stdio.h>
#include <math.h>

int main()
{
    double frequency;
    int midinote = 73;

    frequency = (220.0 * pow(pow(2, 1.0 / 12), 3) * pow(0.5, 5)) * pow(pow(2, 1.0 / 12), midinote);

    //ANSWER: Is less understandable and hard to modify later.
    return 0;
}

/*
    OUTPUT SAMPLE:
        no output
*/