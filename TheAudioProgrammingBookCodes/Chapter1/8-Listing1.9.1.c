//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.9.1 .
//Date: 21/07/2020.

/* sinetext.c */
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
    double twopi = 2.0 * M_PI;
    double angleincr;

    /* set number of points to create */
    nsamps = 51200;

    /* make one complete cycle */
    angleincr = twopi / nsamps;

    for (i = 0; i < nsamps; i++)
    {
        samp = sin(angleincr * i);
        if (0 > fprintf(stdout, "%.21lf\n", samp))
        {
            fprintf(stderr, "error: unable to print on stdout stream\n");
            return 1;
        }
    }

    fprintf(stderr, "done\n");

    return 0;
}