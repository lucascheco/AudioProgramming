/*******************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.3.2 .
    Date:        16/11/2021
********************************************************************************************/
/*(A)*/
#include <portsf.h>

PANPOS constpower(double position) {
    PANPOS pos;
    
    const double root2ovr2 = sqrt(2.0) * 0.5;
    double angle = position * 4.0 * atan(1.0) * 0.5 * 0.5;

    const double cosine = cos(angle);
    const double sine = sin(angle);

    pos.left = root2ovr2 * (cosine - sine);
    pos.right = root2ovr2 * (cosine + sine);

    return pos;
}

/*(B)*/
/*
    sfpan is a program that reads a audiofile and applies panning by reading breakpoints(in a breakpoint 
    file) representing pan positions in time.
*/