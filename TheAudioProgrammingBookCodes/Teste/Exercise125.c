//Author: Lucas Pacheco.
//Description: A tes exercise from "The Audio Programming Book", chapter 1, modifying Listing 1.2 to print sounding length.
//Date: 11/06/2020.

/* listing 1.2. Calculate frequency of a MIDI Note number */
#include <stdio.h>
#include <math.h>

int main()
{
    double length; /* . . . which we want to find, */

    //OBS: I'm not sure about the answer.
    for (int i = 0; i <= 12; i++)
    {
        length = 660.0 * (12.0 * (1.0 / (12.0 + (double)i)));
        printf("%lf\n", length);
    }

    return 0;
}

/*
    OUTPUT SAMPLE:
        660.000000
        609.230769
        565.714286
        528.000000
        495.000000
        465.882353
        440.000000
        416.842105
        396.000000
        377.142857
        360.000000
        344.347826
        330.000000
        
*/