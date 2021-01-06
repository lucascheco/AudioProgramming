/*********************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise1.9.7 .
    Date:        02/08/2020
**********************************************************************************/

/* modifing sinetext.c to 16bit*/
/* write sinewave as a text */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* conditional compilation - is M_PI defined? */
#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI#define M_PI (3.141592654)

int main(int argc, char **argv)
{
    int i, nsamps;
    double samp;
    short ssamp;
    double twopi = 2.0 * M_PI;
    double angleincr;

    /* set number of points to create */
    nsamps = 200;

    /* make one complete cycle */
    angleincr = twopi / nsamps;

    for (i = 0; i < nsamps; i++)
    {
            samp = sin(angleincr * i);
            samp *= 1.0;
            ssamp = (short)(samp * 32767.0);
        if (0 > fprintf(stdout, "%d\n", ssamp))
        {
            fprintf(stderr, "error: unable to print on stdout stream\n");
            return 1;
        }

    }

    fprintf(stderr, "done\n");

    return 0;
}