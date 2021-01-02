/*
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, printing one more frequency.
    Date: 23/05/2020.
*/

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
    ratio = pow(2.0, 1.0 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(ratio, 3.0);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5.0);

    frequency = c0 * pow(ratio, (double)midinote);

    for (int i = 0; i <= notes; i++)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
    }

    for (int i = 0; i <= notes; i++)
    {
        printf("%2d: %lf\n", i + 1, frequencies[i]);
    }

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: Exercises154 24 117
        output1:
             1: 7040.000000
             2: 7458.620184
             3: 7902.132820
             4: 8372.018090
             5: 8869.844191
             6: 9397.272573
             7: 9956.063479
             8: 10548.081821
             9: 11175.303406
            10: 11839.821527
            11: 12543.853951
            12: 13289.750323
            13: 14080.000000
            14: 14917.240369
            15: 15804.265640
            16: 16744.036179
            17: 17739.688383
            18: 18794.545147
            19: 19912.126958
            20: 21096.163642
            21: 22350.606812
            22: 23679.643054
            23: 25087.707903
            24: 26579.500645
            25: 28160.000000 

        output2:
             1: 220.000000
             2: 233.081881
             3: 246.941651
             4: 261.625565
             5: 277.182631
             6: 293.664768
             7: 311.126984
             8: 329.627557
             9: 349.228231
            10: 369.994423
            11: 391.995436
            12: 415.304698
            13: 440.000000
            14: 466.163762
            15: 493.883301
            16: 523.251131
            17: 554.365262
            18: 587.329536
            19: 622.253967
            20: 659.255114
            21: 698.456463
            22: 739.988845
            23: 783.990872
            24: 830.609395
            25: 880.000000
            
*/