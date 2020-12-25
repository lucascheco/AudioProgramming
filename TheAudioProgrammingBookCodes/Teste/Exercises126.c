/*
    Author: Lucas Pacheco.
    Description: A test exercise from "The Audio Programming Book", chapter 1, implement the program fre2midi.
    Date: 11/05/2020.
*/

/*
    OBS: I got very confused about this exercise, so i got help and found this code https://gist.github.com/analoq/771397. 
    It was very helpful to understand this question. 

*/

#include <stdio.h>
#include <math.h>

int main()
{
    double semitone_ratio;
    double c0;        /* for frequency of MIDI Note 0 */
    double c4;        /* for frequency of Middle C */
    double frequency; /* . . . which we want to find, */
    int midinote;     /* . . . given this note. */
    double fracmidi;
    double dif;

    /* calculate required numbers */
    semitone_ratio = pow(2.0, 1.0 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c4 = 220.0 * pow(semitone_ratio, 3.0);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c4 * pow(0.5, 5.0);

    /* find nearest MIDI note to a given frequency in Hz */ 
    /* uses the log rule: log_a(N) = log_b(N) / log_b(a) to find the log of a value to base 'semitone_ratio'. */
    frequency = 430.0;

    fracmidi = log(frequency / c0) / log(semitone_ratio);
    printf("FRACMIDI: %lf\n", fracmidi);

    /* round fracmidi to the nearest whole number */
    midinote = (int)(fracmidi + 0.5);
    printf("MIDINOTE: %d\n", midinote);

    /* Extract decimals */
    dif = fracmidi - (double)midinote;
    printf("Difference: %lf\n", dif);

    /* Percentage */
    dif *= 100;

    printf("The nearest MIDI note to frequency %.1f is %d with pitch bend of %.1f%%\n", frequency, midinote, dif);

    return 0;
}

/*
    OUTPUT SAMPLE:
        FRACMIDI: 68.601998
        MIDINOTE: 69
        Difference: -0.398002
        The nearest MIDI note to frequency 430.0 is 69 with pitch bend of -39.8%

*/