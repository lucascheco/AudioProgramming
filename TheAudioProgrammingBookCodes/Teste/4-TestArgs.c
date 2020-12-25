/*
    Author: Lucas Pacheco.
    Description: A test program from "The Audio Programming Book", about argc, argv.
    Date: 17/05/2020.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    double c5, c0, semitoneratio;
    double frequency;
    int midinote; /* could be a char */

    semitoneratio = pow(2, 1.0 / 12);

    c5 = 220.0 * pow(semitoneratio, 3);

    c0 = c5 * pow(0.5, 5);

    /* if the program is not called cpsmidi, either change the lines below, or use the argv[0] system, shown commented out below */
    if (argc != 2)
    {
        printf("cpsmidi : converts MIDI note to frequency.\n" /*,argv[0]*/);
        printf("usage: cpsmidi MIDInote\n" /* ,argv[0]*/);
        printf(" range: 0 <= MIDInote <= 127 \n");
        return 1;
    }

    midinote = atoi(argv[1]);
    /* use argv[1] to echo a bad argument string to the user */
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

    frequency = c0 * pow(semitoneratio, midinote);

    printf("frequency of MIDI note %d = %f\n", midinote, frequency);

    return 0;
}

/*
    OBS: Windows--
            compile:gcc -o 4-TestArgs 4-TestArgs.c
            run:4-TestArgs 126
    OUTPUTSAMPLE:
        frequency of MIDI note 126 = 11839.821527

*/