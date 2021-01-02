/*
    Author: Lucas Pacheco.
    Description: A test program from "The Audio Programming Book", while example2.
    Date: 129/12/2020.
*/

#include <stdio.h>
#include <math.h>

int main()
{
    double ratio = 1.0, semitone_ratio = pow(2.0, 1.0 / 12.0);
    double interval[12];

    int i = 0;

    while (i < 12)
    {
        printf("%d = %lf\n", i, interval[i++] = ratio);
        ratio *= semitone_ratio; 
    }

    return 0;
}

/*
    OUTPUTSAMPLE:
        1 = 1.000000
        2 = 1.059463
        3 = 1.122462
        4 = 1.189207
        5 = 1.259921
        6 = 1.334840
        7 = 1.414214
        8 = 1.498307
        9 = 1.587401
        10 = 1.681793
        11 = 1.781797
        12 = 1.887749
*/
