/*
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, writing a program to create musical scales.
    Date: 22/05/2020.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double c5,  c0, semitone_ratio;
    double frequency;
    int midinote;

    semitone_ratio = pow(2.0, 1.0 / 12.0);
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);

    /* 
        If the program is not called 4-Listing1.4, either change the lines below, 
        or use the argv[0] system, shown commented out below.
    */
    if (argc != 2)  
    {
        printf("4-Listing1.4 : converts MIDI note to frequency. \n" /* , argv[0] */);
        printf("usage: 4-Listing MIDInote.\n" /* , argv[0] */);
        printf(" range: 0 <= MIDInote <= 127 \n");
        return 1;
    }

    midinote = atoi(argv[1]);

    /* Use argv[1] to echo a bad argument string to the user */
    if (midinote < 0)
    {
        printf("Bad MIDI note value: %s\n", argv[1]);
        return 1;
    }

    if (midinote > 127)
    {
        printf("%s is beyond the MIDI range!\n", argv[1]);
        return 1;
    }

    frequency = c0 * pow(semitone_ratio, (double)midinote);

    printf("Frequency pf MIDI note %d = %f\n", midinote, frequency);

    return 0;
}