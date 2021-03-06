/*
    Author: Lucas Pacheco.
    Description: A copy from "The Audio Programming Book", chapter 0, A Program for Analyzing Serial Music.
    Date: 05/05/2020.
*/

#include <stdio.h>
#include <stdlib.h>

int mod12(int note)
{
    while (note >= 12)
        note -= 12;
    while (note < 0)
        note += 12;

    return note;
}

int main(int argc, char **argv)
{
    int series[12][12], offset;
    int n, m, i;
    char *table[12] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

    if (argc != 13)
    {
        printf("usage: %s note1 note2 ... note12\n", argv[0]);
        return -1;
    }

    /* loop until all available notes are entered*/
    for (n = 0; n < 12; n++)
        series[0][n] = mod12(atoi(argv[n + 1]));

    /* create inversion in column 1 */
    for (m = 1; m < 12; m++)
        series[m][0] = mod12(series[m - 1][0] + series[0][m - 1] - series[0][m]);

    /* create all transpositions */
    for (m = 1; m < 12; m++)
        for (n = 1; n < 12; n++)
            series[m][n] = mod12(series[0][n] + series[m][0] - series[0][0]);

    for (m = 0; m < 12; m++)
    { /* print the pitch classes, row by row, using the translation table */
        for (n = 0; n < 12; n++)
            printf(" %s ", table[series[m][n]]);
        printf("\n");
    }

    return 0;
}

/*
    OUTPUT SAMPLE:
        Running the code with twelve ramdom arguments -> 6-AProgramForAnalyzingSerialMusic 0 2 4 5 2 4 0 4 5 4 0 2
    Output:
        C  D  E  F  D  E  C  E  F  E  C  D
        Bb  C  D  Eb  C  D  Bb  D  Eb  D  Bb  C
        Ab  Bb  C  Db  Bb  C  Ab  C  Db  C  Ab  Bb
        G  A  B  C  A  B  G  B  C  B  G  A
        Bb  C  D  Eb  C  D  Bb  D  Eb  D  Bb  C
        Ab  Bb  C  Db  Bb  C  Ab  C  Db  C  Ab  Bb
        C  D  E  F  D  E  C  E  F  E  C  D
        Ab  Bb  C  Db  Bb  C  Ab  C  Db  C  Ab  Bb
        G  A  B  C  A  B  G  B  C  B  G  A
        Ab  Bb  C  Db  Bb  C  Ab  C  Db  C  Ab  Bb
        C  D  E  F  D  E  C  E  F  E  C  D
        Bb  C  D  Eb  C  D  Bb  D  Eb  D  Bb  C
*/