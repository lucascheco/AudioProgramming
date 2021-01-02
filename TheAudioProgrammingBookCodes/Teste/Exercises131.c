/*
    Author: Lucas Pacheco.
    Description: A test from "The Audio Programming Book", chapter 1, Listing 1.3.
    Date: 13/05/2020.
*/

/* listing 1.3. Calculate frequency of a MIDI Note number */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double c5, c0, semitone_ratio, frequency;
    int midinote;
    char message[256];
    char *result;

    /* Semitone ratio calculation. */
    semitone_ratio = pow(2, 1.0 / 12);

    /* C5 3 semitones down from A4. */
    c5 = 220.0 * pow(semitone_ratio, 3);

    /* C0 5 octaves above C5. */
    c0 = c5 * pow(0.5, 5);

    printf("Enter MIDI note (0 - 127): ");

    /* "result" get a adress, if is NULL the program will crash. */
    result = gets(message);

    if (result == NULL)
    {
        printf("There was an error reading the input.\n");
        return 1;
    }

    /* If the user only press the enter key. */
    if (message[0] == '\0')
    {
        printf("Have a nice day!\n");
        return 1;
    }

    /* Here a conversion string to int. */
    midinote = atoi(message);

    /* Making sure to not overcome boundaries, range of MIDI is 0 - 127 inclusive. */
    if (midinote < 0)
    {
        printf("Sorry - %s is a bad MIDI note number\n", message);
        return 1;
    }

    if (midinote > 127)
    {
        printf("Sorry - %s is beyond the MIDI range!\n", message);
        return 1;
    }

    /* Frequency calculation. */
    frequency = c0 * pow(semitone_ratio, midinote);

    printf("frequency of MIDI note %d = %f\n", midinote, frequency);

    return 0;
}

/*
    OUTPUT SAMPLE:
        Enter MIDI note (0 - 127): 54
        frequency of MIDI note 54 = 184.997211
*/