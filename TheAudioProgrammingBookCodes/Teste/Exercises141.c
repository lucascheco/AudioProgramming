//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", chapter 1, covert all programs developed so far to use argc and argv.
//Date: 17/05/2020.

/*
    OBS: Exercises 141 , 142, 143(a) in the same file. 143(b) was jumped.
*/

//Exercise 1.4.1 (obs: To simplify, I only implemented one code).
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    double semitone_ratio;
    double c0;        /* for frequency of MIDI Note 0 */
    double c5;        /* for frequency of Middle C */
    double frequency; /* . . . which we want to find, */
    int    midinote;     /* . . . given this note. */
    double fracmidi;
    double dif;
    char   *rootA_string = argv[2];
    double rootA;

    //Exercise 1.4.2
    if (argc != 3)
    {
        printf("Exercises141: finds the nearest MIDI note to a frequency.\n" /*,argv[0]*/);
        printf("usage: Exercises frequency rootA\n" /* ,argv[0]*/);
        printf("range: 20.000 <= frequency <= 20000.000 \n");
        return 1;
    }
    
    frequency = atof(argv[1]);

    //Exercise 1.4.3 (a).
    if(strcmp(rootA_string, "standard") == 0)
    {
        printf("You choose STANDARD ROOT.\n");
        rootA = 440.0;
    }
    else if(strcmp(rootA_string, "baroque") == 0)
    {
        printf("You choose BAROQUE ROOT.\n");
        rootA = 415.0;
    }
    else
    {
        printf("Exercises141: finds the nearest MIDI note to a frequency.\n");
        printf("usage: Exercises frequency rootA\n");
        printf("range: 20.000 <= frequency <= 20000.000 \n");
        printf("error: INVALID ROOT\n");
        printf("Please choose 'standard' or 'baroque'\n");

        return 1;
    }
    
    /* calculate required numbers */
    semitone_ratio = pow(2, 1 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = (rootA / 2) */
    c5 = (rootA / 2) * pow(semitone_ratio, 3);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    /* find nearest MIDI note to a given frequency in Hz */ /* uses the log rule: log_a(N) = log_b(N) / log_b(a) to find the log of a value to base 'semitone_ratio'. */
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    printf("FRACMIDI: %lf\n", fracmidi);

    /* round fracmidi to the nearest whole number */
    midinote = (int)(fracmidi + 0.5);
    printf("MIDINOTE: %d\n", midinote);

    /* Extract decimals */
    dif = fracmidi - (double)midinote;
    printf("Difference: %f\n", dif);

    /* Percentage */
    dif *= 100;

    printf("The nearest MIDI note to frequency %.1f is %d with pitch bend of %.1f%%\n", frequency, midinote, round(dif));

    return 0;
}

/*
    OUTPUT SAMPLE 1:
    Windows commandline: Exercises141 1223 deafaefihefa
        output:
            Exercises141: finds the nearest MIDI note to a frequency.
            usage: Exercises frequency rootA
            range: 20.000 <= frequency <= 20000.000 
            error: INVALID ROOT
            Please choose 'standard' or 'baroque'
*/

/*
    OUTPUT SAMPLE 2:
    Windows commandline: Exercises141 1223 standard
        output:
            You choose STANDARD ROOT
            FRACTMIDI: 86.698188
            MIDINOTE: 87
            Difference: -0.301812
            The nearest MIDI note to frequency 1223.0 is 87 with pitch bend of -30.0%
*/