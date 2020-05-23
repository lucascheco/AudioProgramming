//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, printing one more frequency.
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
    for (int i = 0; i <= notes; i++)
    {
        frequencies[i] = frequency;
        frequency *= ratio;
    }

    for (int i = 0; i <= notes; i++)
    {
        printf("%d: %lf\n", i + 1, frequencies[i]);
    }

    return 0;
}

/*
    OUTPUSAMPLE:
    Windows commandline: Exercises154 24 117
        output:
            1: 220.000000                                                                                                                                                                      
            2: 226.446492                                                                                                                                                                      
            3: 233.081881                                                                                                                                                                      
            4: 239.911701                                                                                                                                                                      
            5: 246.941651                                                                                                                                                                      
            6: 254.177593                                                                                                                                                                      
            7: 261.625565                                                                                                                                                                      
            8: 269.291780                                                                                                                                                                      
            9: 277.182631                                                                                                                                                                      
            10: 285.304702
            11: 293.664768                                                                                                                                                                     
            12: 302.269802                                                                                                                                                                     
            13: 311.126984                                                                                                                                                                     
            14: 320.243700                                                                                                                                                                     
            15: 329.627557                                                                                                                                                                     
            16: 339.286382                                                                                                                                                                     
            17: 349.228231                                                                                                                                                                     
            18: 359.461400                                                                                                                                                                     
            19: 369.994423  
            20: 380.836087                                                                                                                                                                     
            21: 391.995436                                                                                                                                                                     
            22: 403.481779                                                                                                                                                                     
            23: 415.304698                                                                                                                                                                     
            24: 427.474054                                                                                                                                                                     
            25: 440.000000  

*/