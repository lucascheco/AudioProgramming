//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.9.3 .
//Date: 22/07/2020.

/* tfork.c virtual tuning fork combining sinetext.c and expdecay.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI#define M_PI (3.141592654)

/* define our program argument list */
enum {ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, ARG_SR, ARG_SLOPE, ARG_NARGS};

int main(int argc, char **argv)
{
    int    i, sr, nsamps;
    double samp, dur, freq, srate, k, a, x, slope;
    double angleincr;
    double twopi   = 2.0 * M_PI;
    double maxsamp = 0.0;
    FILE   *fp     = NULL;

    if (argc != ARG_NARGS)
    {
        fprintf(stderr, "Usage: tfork outfile.txt dur freq srate slope\n");
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
    slope  = atof(argv[ARG_SLOPE]);

    nsamps    = (int)(dur * srate);
    angleincr = twopi * freq / srate;
    k         = dur / nsamps;
    a         = exp(-k / slope);
    x         = 1.0;

    for (i = 0; i < nsamps; i++)
    {
        samp = sin(angleincr * i);
        
        /* apply exp decay */
        x    *= a;
        samp *= x;
        fprintf(fp, "%.8lf\n", samp);
    }

    fclose(fp);
    
    printf("done\n");

    return 0;
}