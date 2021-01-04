/***********************************************************************************
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.8.1 .
    Date: 08/07/2020.
************************************************************************************/

/* expdecay.c */
/* implement formula x[t] = a * exp(-k/T) */
/* This also outputs to a text file. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    int    i, nsteps;
    double step, x, a, T, k;
    double dur;
    FILE   *fp;

    fp = fopen("expdecay.txt", "w");
    /* Basically dur = duration of the decay, T shallowness*/
    if (argc != 5)
    {
        printf("usage: expdecay dur T steps expdecay.txt\n");
        return 1;
    }

    dur    = atof(argv[1]);
    T      = atof(argv[2]);
    nsteps = atoi(argv[3]);

    k    = dur / nsteps; /* the constant time increment */
    a    = exp(-k / T);  /* calc the constant ratio value */
    x    = 1.0;          /* starting value for the decay */
    step = 0.0;

    for (i = 0; i < nsteps; i++)
    {
        printf(     "%.4lf\t%.8lf\n", step, x);
        fprintf(fp, "%.4lf\t%.8lf\n", step, x);
        x *= a;
        step += k;
    }

    fclose(fp);

    return 0;
}