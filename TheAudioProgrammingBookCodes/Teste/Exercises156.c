/*
    Author: Lucas Pacheco.
    Description: A test exercise from "The Audio Programming Book", chapter 1, exercise 1.5.7 .
    Date: 31/12/2020.
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
        /* TODO: print CSOUND commands to a text file. */
    }

    return 0;
}
