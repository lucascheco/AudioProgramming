//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.9.4 .
//Date: 22/07/2020.

/* tfork2.c alternate tuning fork generator based on expbrk.c 
* - decay is always to ~silencer regardless of duration. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI#define M_PI (3.141592654)

/* define our program argument list */
enum {ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, ARG_SR, ARG_AMP, ARG_NARGS};

int main(int argc, char **argv)
{
    int    i, sr, nsamps;
    double samp, dur, freq, srate, k, amp, maxamp;
    double start, end, fac, angleincr;
    double twopi   = 2.0 * M_PI;
    FILE   *fp     = NULL;

    if (argc != ARG_NARGS)
    {
        fprintf(stderr, "Usage: tfork2 outfile.txt dur freq srate amp\n");
        return 1;
    }

    if ((fp = fopen(argv[ARG_OUTFILE], "w")) == NULL)
    {
        fprintf(stderr, "Error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    dur    = atof(argv[ARG_DUR]);
    freq   = atof(argv[ARG_HZ]);
    srate  = atof(argv[ARG_SR]);
    amp    = atof(argv[ARG_AMP]);

    nsamps    = (int)(dur * srate);
    angleincr = twopi * freq / srate;

    start = 1.0;
    end   = 1.0e-4; /* =  -80dB */

    maxamp = 0.0;

    fac = pow(end / start, 1.0/nsamps);

    for (i = 0; i < nsamps; i++)
    {
        samp = amp * sin(angleincr * i);
        samp *= start;
        start *= fac;

        if (0 > fprintf(fp, "%.8lf\n", samp))
        {
            fprintf(stderr, "error: unable to print on FILE stream\n");
            return 1;
        }

        if (fabs(samp) > maxamp)
            maxamp = fabs(samp);
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "error: unable to close the FILE stream\n");
        return 1;
    }
    
    printf("done. Maximum sample value = %.8lf\n", maxamp);

    return 0;
}