/*
    Author: Lucas Pacheco.
    Description: A test exercise from "The Audio Programming Book", chapter 1, adding one more argument.
    Date: 23/05/2020.
*/

/* OBS: I don't totally got it this question. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int notes, midinote;
    double frequency, ratio;
    double c0, c5;
    double frequencies[200];
    double interval;
    int intervalInt;

    /*
        ERROR HANDLE 
    */

    if (argc != 4)
    {
        printf("usage: nscale notes midinote interval\n");
        return 1;
    }

    notes = atoi(argv[1]);

    if (notes < 1)
    {
        printf("Error: notes must be positive\n");
        return 1;
    }

    if (notes > 24)
    {
        printf("Error: maximum value for notes is 24\n");
        return 1;
    }

    midinote = atoi(argv[2]);

    if (midinote < 0)
    {
        printf("Error: cannot have negative MIDI notes!\n");
        return 1;
    }

    if (midinote > 127)
    {
        printf("Error: maximum MIDInote is 127\n");
        return 1;
    }

    interval = atof(argv[3]);

    if (interval < 0.0)
    {
        printf("Error: interval must be positive.\n");
        return 1;
    }

    /*
        Functionality
    */

    /* calculate required numbers */
    ratio = pow(2.0, 1.0 / (double)notes);

    /* find Middle C, three semitones above low A4 = 220 */
    c5 = 220.0 * pow(ratio, 3.0);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    frequency = c0 * pow(ratio, midinote);

    ratio = pow(interval, 1.0 / (double)notes);

    for (int i = 0; i < notes; i++)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
    }

    for (int i = 0; i < notes; i++)
    {
        printf("%d: %lf\n", i + 1, frequencies[i]);
    }

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: Exercises155 24 117 3.0
        output:
             1: 220.000000
             2: 230.304664
             3: 241.091992
             4: 252.384592
             5: 264.206130
             6: 276.581382
             7: 289.536283
             8: 303.097983
             9: 317.294905
            10: 332.156803
            11: 347.714822
            12: 364.001569
            13: 381.051178
            14: 398.899379
            15: 417.583580
            16: 437.142936
            17: 457.618441
            18: 479.053006
            19: 501.491553
            20: 524.981107
            21: 549.570897
            22: 575.312458
            23: 602.259738
            24: 630.469212
            
*/