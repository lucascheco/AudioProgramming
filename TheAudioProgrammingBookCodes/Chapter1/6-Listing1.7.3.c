/***********************************************************************************
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.7.3 .
    Date: 10/06/2020.
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TIME double
#define VALUE double

typedef struct breakpoint
{
    TIME time;
    VALUE value;
} BREAKPOINT;

BREAKPOINT* get_breakpoints(FILE *fp, long *psize)
{
    int got;
    long npoints = 0, size = 64;
    TIME lasttime = 0.0;
    BREAKPOINT *points = NULL;
    char line[80];

    if (fp == NULL)
        return NULL;

    points = (BREAKPOINT *)malloc(sizeof(BREAKPOINT) * size);

    if (points == NULL)
        return NULL;

    while (fgets(line, 80, fp))
    {
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);

        if (got < 0)
            continue;

        if (got == 0)
        {
            printf("Line %d has non-numeric data\n", npoints + 1);
            break;
        }

        if (points[npoints].time < lasttime)
        {
            printf("data error at point %d: time not increasing\n", npoints + 1);
            break;
        }

        lasttime = points[npoints].time;

        if (++npoints == size)
        {
            BREAKPOINT *temp;
            size += npoints;

            temp = (BREAKPOINT *)realloc(points, sizeof(BREAKPOINT) * size);

            if (temp == NULL)
            {
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }

            points = temp;
        }
    }

    if (npoints)
        *psize = npoints;

    return points;
}
