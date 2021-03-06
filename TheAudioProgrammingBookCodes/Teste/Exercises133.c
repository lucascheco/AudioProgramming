/*
    Author: Lucas Pacheco.
    Description: A test from "The Audio Programming Book", chapter 1, adding a test case.
    Date: 14/05/2020.
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

    semitone_ratio = pow(2, 1.0 / 12);

    c5 = 220.0 * pow(semitone_ratio, 3);

    c0 = c5 * pow(0.5, 5);

    printf("Enter MIDI note (0 - 127): ");

    result = fgets(message, 256, stdin);

    if (result == NULL)
    {
        printf("There was an error reading the input.\n");
        return 1;
    }

    if (message[0] == '\0')
    {
        printf("Have a nice day!\n");
        return 1;
    }

    /* ANSWER (a) */
    /*
        if (1 == 1.0)
        {
            printf(" == \n");
        }
        else
        {
            printf(" != \n");
        }
    */
    /* If we type a float will trigger this if statement. */
    if (atof(message) != atoi(message))
    {
        printf("please, enter a integer value\n");
        return 1;
    }

    midinote = atoi(message);

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

    frequency = c0 * pow(semitone_ratio, midinote);

    printf("frequency of MIDI note %d = %f\n", midinote, frequency);

    return 0;
}

/*
    OUTPUT SAMPLE:
        Enter MIDI note (0 - 127): 54
        frequency of MIDI note 54 = 184.997211
*/
/*
    OUTPUT SAMPLE:
        Enter MIDI note (0 - 127): 1.2
        please, enter a integer value
*/