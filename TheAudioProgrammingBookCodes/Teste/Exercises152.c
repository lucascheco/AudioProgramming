//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", chapter 1, changing loop types.
//Date: 23/05/2020.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int notes, midinote;
    double frequency, ratio;
    double c0, c5;
    double frequencies[24];

    /*
        ERROR HANDLE 
    */
    if (argc != 3)
    {
        printf("usage: nscale notes midinote\n");
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

    /*
        Functionality
    */

    /* calculate required numbers */
    ratio = pow(2, 1.0 / (double)notes); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(ratio, 3);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    frequency = c0 * pow(ratio, midinote);

    // 1.5.2(A)
    int i = 0;
    while (i < notes)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
        i++;
    }

    // 1.5.2(B)
    i = 0;
    do
    {
        printf("%lf\n", frequencies[i]);
        i++;
    } while (i < notes);

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: Exercises152 24 117
        output:
            220.000000
            226.446492
            233.081881
            239.911701
            246.941651
            254.177593
            261.625565
            269.291780
            277.182631
            285.304702
            293.664768
            302.269802
            311.126984
            320.243700
            329.627557
            339.286382
            349.228231
            359.461400
            369.994423
            380.836087
            391.995436
            403.481779
            415.304698
            427.474054

*/