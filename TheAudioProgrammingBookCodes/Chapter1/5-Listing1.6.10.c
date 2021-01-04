/*************************************************************************************
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.10 .
    Date: 01/06/2020.
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
    usage iscale [-m][-i] N startval [outfile.txt]
    -m : sets format of startval as MIDI note  
    -i : prints the calculated interval as well as the abs freq  
    outfile: optional text filename for output data
*/
/* To use optional flags, we assume this flags are before the required ones. */
/* We are not passing values, just flags, thus the program has multiples paths. */

int main(int argc, char *argv[])
{
    int notes, i;
    int ismidi = 0;
    int write_interval = 0;
    int err = 0;
    double startval, basefreq, ratio;
    FILE *fp;
    double intervals[25];

    /* check first arg for flag option: argc at least 2 */
    while (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'm')
                ismidi = 1;

            else if (argv[1][1] == 'i')
                write_interval = 1;

            else
            {
                printf("error: unrecognized option %s\n", argv[1]);

                return 1;
            }

            /* step up to next arg */
            argc--;
            argv++;
        }
        else
            break;
    }

    /* required arguments */
    if (argc < 3)
    {
        printf("insufficient arguments\n");
        printf("Usage: itable [-m][-i] N startval [outfile.txt]\n");

        return 1;
    }

    /*
        Now read and check all arguments
        We now expected argv[1] to hold N and argv[2] startval
    */
    notes = atoi(argv[1]);

    if (notes < 1 || notes > 24)
    {
        printf("error: N out of range. Must be between 1 and 24.\n");

        return 1;
    }

    startval = atof(argv[2]);

    if (ismidi)
    {
        if (startval > 127.0)
        {
            printf("error: MIDI startval must be <= 127.\n");

            return 1;
        }

        /* for MIDI, startval = 0 is legal */
        if (startval < 0.0)
        {
            printf("error: MIDI startval must be >= 0.\n");

            return 1;
        }
    }
    else
    /*
        it's freq: must be positive number
        check low limit
    */
    {
        if (startval <= 0.0)
        {
            printf("error: frequency startval must be positive.\n");

            return 1;
        }
    }

    /* check for optional filename */
    fp = NULL;

    if (argc == 4)
    {
        fp = fopen(argv[3], "w");

        if (fp == NULL)
        {
            printf("WARNING: unable to create file %s\n", argv[3]);
            perror("");
        }
    }

    /*
        all params ready - fill array and write to file if created
        find basefreq, if val is MIDI
    */

    if (ismidi)
    {
        double c0, c5;

        /* find base MIDI note */
        ratio = pow(2.0, 1.0 / 12.0);
        c5 = 220.0 * pow(ratio, 3);
        c0 = c5 * pow(0.5, 5);
        basefreq = c0 * pow(ratio, startval);
    }
    else
        basefreq = startval;

    /* calc ratio from notes and fill the array */
    ratio = pow(2.0, 1.0 / (double)notes);

    for (i = 0; i <= notes; i++)
    {
        intervals[i] = basefreq;
        basefreq *= ratio;
    }

    /* finally, read array, write to screen, and optionally to file */

    for (i = 0; i <= notes; i++)
    {
        if (write_interval)
            printf("%d: \t%f\t%f\n", i, pow(ratio, i), intervals[i]);
        else
            printf("%d: \t%f\n", i, intervals[i]);

        if (fp)
        {
            if (write_interval)
                err = fprintf(fp, "%d: \t%f\t%f\n", i, pow(ratio, i), intervals[i]);
            else
                err = fprintf(fp, "%d: \t%f\n", i, intervals[i]);

            if (err < 0)
                break;
        }
    }

    if (err < 0)
        perror("There was an error writing the file.\n");

    if (fp)
        fclose(fp);

    return 0;
}

/*
    OUTPUTSAMPLE:
        input: 
            ./5-Listing1.6.10 -m -i 12 57
        output: 
            0:      1.000000        220.000000
            1:      1.059463        233.081881
            2:      1.122462        246.941651
            3:      1.189207        261.625565
            4:      1.259921        277.182631
            5:      1.334840        293.664768
            6:      1.414214        311.126984
            7:      1.498307        329.627557
            8:      1.587401        349.228231
            9:      1.681793        369.994423
            10:     1.781797        391.995436
            11:     1.887749        415.304698
            12:     2.000000        440.000000
*/

/*
    OUTPUTSAMPLE:
        input: 
            ./5-Listing1.6.10 -i 12 220
        output: 
            0:      1.000000        220.000000
            1:      1.059463        233.081881
            2:      1.122462        246.941651
            3:      1.189207        261.625565
            4:      1.259921        277.182631
            5:      1.334840        293.664768
            6:      1.414214        311.126984
            7:      1.498307        329.627557
            8:      1.587401        349.228231
            9:      1.681793        369.994423
            10:     1.781797        391.995436
            11:     1.887749        415.304698
            12:     2.000000        440.000000
*/

/*
    OUTPUTSAMPLE:
        input: 
            ./5-Listing1.6.10 -i 12 57
        output: 
            0:      1.000000        57.000000
            1:      1.059463        60.389396
            2:      1.122462        63.980337
            3:      1.189207        67.784806
            4:      1.259921        71.815500
            5:      1.334840        76.085872
            6:      1.414214        80.610173
            7:      1.498307        85.403503
            8:      1.587401        90.481860
            9:      1.681793        95.862191
            10:     1.781797        101.562454
            11:     1.887749        107.601672
            12:     2.000000        114.000000
*/