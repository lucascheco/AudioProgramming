//Author: Lucas Pacheco.
//Description: Test exercise from "The Audio Programming Book", chapter 1, Exercises 1.7.1 .
//Date: 11/06/2020.

#include <stdio.h>
#include <stdlib.h>

#define TIME double
#define VALUE double

typedef struct breakpoint
{
    TIME time;
    VALUE value;
} BREAKPOINT;

/* input: points = array of BREAKPOINTS, npoints gives the length of the array */
BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints);
/* output: copy of the BREAKPOINT containing largest value */

int main(void)
{
    return 0;
}

BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints)
{

    int i;
    BREAKPOINT point = {0.0, 0.0};

    if (points == NULL)
        return point;

    point.time = points[0].time;
    point.value = points[0].value;

    for (i = 1; i < npoints; i++)
    {
        if (points[i].value > point.value)
        {
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }

    return point;
}