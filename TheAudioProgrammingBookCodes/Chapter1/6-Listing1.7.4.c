//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.7.4,  .
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

BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints);

BREAKPOINT *get_breakpoints(FILE *fp, long *psize);

int main(int argc, char *argv[])
{
    long size;
    TIME dur;
    BREAKPOINT point, *points;
    FILE *fp;

    printf("breakdur: find duration of breakpoint file\n");

    if (argc < 2)
    {
        printf("usage: breakdur infile.txt\n");
        return 0;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        return 0;

    size = 0;

    points = get_breakpoints(fp, &size);

    if (points == NULL)
    {
        printf("No breakpoints read.\n");
        fclose(fp);
        return 1;
    }

    if (size < 2)
    {
        printf("Error: at least two breakpoints required\n");
        free(points);
        fclose(fp);
        return 1;
    }

    /* required breakpoints to start from 0 */
    if (points[0].time != 0.0)
    {
        printf("Error in breakpoint data: first time must be 0.0\n");
        free(points);
        fclose(fp);
        return 1;
    }

    printf("read %d breakpoints\n", size);

    dur = points[size - 1].time;

    printf("duration: %f seconds\n", dur);

    point = maxpoint(points, size);

    printf("maximum value: %f at %f secs\n", point.value, point.time);

    free(points);
    fclose(fp);

    return 0;
}

/* FUNCTIONS*/
BREAKPOINT *get_breakpoints(FILE *fp, long *psize)
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

BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints)
{
    int i;
    BREAKPOINT point;

    point.time = points[0].time;
    point.value = points[0].value;

    for (i = 0; i < npoints; i++)
    {
        if (points[i].value > point.value)
        {
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }

    return point;
}
