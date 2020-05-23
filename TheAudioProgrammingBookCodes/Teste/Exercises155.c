//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", chapter 1, adding one more argument.
//Date: 23/05/2020.

// OBS: I don't totally got it this question.

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

    if (interval < 1.0)
    {
        printf("Error: interval must be greater than 1.0\n");
        return 1;
    }

    if (interval > 12.0)
    {
        printf("Error: interval must be lower than 12.0\n");
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

    if (interval < 1.0)
    {

        for (int i = 0; i < notes / 2; i++)
        {
            frequencies[i] = frequency;
            frequency *= ratio;
        }

        for (int i = 0; i < notes / 2; i++)
        {
            printf("%lf\n", frequencies[i]);
        }
    }
    else if (interval < 12.0)
    {
        intervalInt = (int)(interval / 2);
        for (int i = 0; i < notes * intervalInt; i++)
        {
            frequencies[i] = frequency;
            frequency *= ratio;
        }

        for (int i = 0; i < notes * intervalInt; i++)
        {
            printf("%lf\n", frequencies[i]);
        }
    }

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: Exercises155 24 117 4.0
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
            440.000000
            452.892984
            466.163762
            479.823402
            493.883301
            508.355187
            523.251131
            538.583559
            554.365262
            570.609404
            587.329536
            604.539605
            622.253967
            640.487400
            659.255114
            678.572763
            698.456463
            718.922799
            739.988845
            761.672174
            783.990872
            806.963558
            830.609395
            854.948108

*/