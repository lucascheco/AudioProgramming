/*
    Author: Lucas Pacheco.
    Description: A test exercise from "The Audio Programming Book", chapter 1, changing loop types.
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
    
    int i = 0;

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
    ratio = pow(2, 1.0 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(ratio, 3);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    frequency = c0 * pow(ratio, midinote);

    ratio = pow(2.0, 1.0 / (double)notes);
    
    /* 1.5.2(A) */
    while (i < notes)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
        i++;
    }

    /* 1.5.2(B) */
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

*/