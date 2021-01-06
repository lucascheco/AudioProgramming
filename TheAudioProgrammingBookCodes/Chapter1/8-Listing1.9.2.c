/***********************************************************************************
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.9.2 .
    Date: 21/07/2020.
************************************************************************************/

/* sinetext2.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* conditional compilation - is M_PI defined? */
#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI#define M_PI (3.141592654)

/* define our program argument list */
enum {ARG_NAME, ARG_NSAMPS, ARG_FREQ, ARG_SR, ARG_NARGS};

int main(int argc, char **argv)
{
    int i, nsamps;
    double samp, freq, srate;
    double twopi = 2.0 * M_PI;
    double angleincr;

    if (argc != ARG_NARGS)
    {
        fprintf(stderr, "Usage: sinetext2 nsamps freq srate\n");
        return 1;
    }

    nsamps = atoi(argv[ARG_NSAMPS]);
    freq   = atof(argv[ARG_FREQ]);
    srate  = atof(argv[ARG_SR]);

    angleincr = twopi * freq / srate;

    for (i = 0; i < nsamps; i++)
    {
        samp = sin(angleincr * i);
        
        if (0 > fprintf(stdout, "%.10lf\n", samp))
        {
            fprintf(stderr, "error: unable to print on stdout stream\n");  
            return 1;          
        }
    }

    fprintf(stderr, "done\n");

    return 0;
}