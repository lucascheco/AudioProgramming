/*
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, writing a program to create musical scales.
    Date: 22/05/2020.
*/

/* nscale  Display E.T(EqualTempered) frequencies for a N-note octave, from a given MIDI note */
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
        Erro handling. 
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
    ratio = pow(2.0, 1.0 / 12.0);  /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(ratio, 3.0);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5.0);

    frequency = c0 * pow(ratio, (double)midinote);

    /* Custom ratio -> User Input */
    ratio = pow(2.0, 1.0 / (double)notes);

    for (int i = 0; i < notes; i++)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
    }

    for (int i = 0; i < notes; i++)
    {
        printf("%lf\n", frequencies[i]);
    }

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: 4-Listing1.5.3 24 117
        output1:
            7040.000000
            7246.287746
            7458.620184
            7677.174438
            7902.132820
            8133.682986
            8372.018090
            8617.336945
            8869.844191
            9129.750465
            9397.272573
            9672.633678
            9956.063479
            10247.798407
            10548.081821
            10857.164211
            11175.303406
            11502.764791
            11839.821527
            12186.754779
            12543.853951
            12911.416928
            13289.750323
            13679.169731

        output2:
            146.832384
            155.563492
            164.813778
            174.614116
            184.997211
            195.997718
            207.652349
            220.000000
            233.081881
            246.941651
            261.625565
            277.182631
        
*/