//Author: Lucas Pacheco.
//Description: Test exercise from "The Audio Programming Book", chapter 1, Exercises 1.7.4 .
//Date: 11/06/2020.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FileMenu.c"

#define TIME  double
#define VALUE double

typedef struct breakpoint
{
    TIME time;
    VALUE value;
} BREAKPOINT;


BREAKPOINT *get_breakpoints(FILE *fp, unsigned long *psize);

BREAKPOINT maxpoint(const BREAKPOINT *points, unsigned long npoints);

/* NEW functions */
BREAKPOINT *stretch_times(FILE *fp, BREAKPOINT *points, unsigned long size, TIME timeFactor);

BREAKPOINT *normalize(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE normalFactor);

BREAKPOINT *shift_Up(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor);

BREAKPOINT *shift_Down(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor);

BREAKPOINT *scale_by_factor(FILE *fp, BREAKPOINT *points, unsigned long *size, unsigned long scaleFactor);

BREAKPOINT *truncate(FILE *fp, unsigned long *size);

BREAKPOINT *extend(FILE *fp, unsigned long *size);

int *insert_point(FILE *fp, BREAKPOINT p);

int *delete_point(FILE *fp, unsigned long *size, BREAKPOINT p);

/* MAIN FUNCTION */
int main(int argc, char *argv[])
{
    unsigned long size;
    TIME dur;
    BREAKPOINT point_to_Store, *points, to_add;
    FILE *fp;
    char *file_name;
    flagOption *flag;
    flag = (flagOption *)malloc(sizeof(flagOption *));

    file_name = argv[1];
    
    to_add.time = 3.000000; 
    to_add.value = 5.017500;

    printf("breakdur: find duration of breakpoint file\n");

    if (argc < 2)
    {
        printf("usage: breakdur infile.txt\n");
        return 0;
    }

    fp = menu_mode(fp, file_name, flag);

    if (fp == NULL)
    {
        printf("No FILE opened.\n");
        return 0;
    }

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
   
    //stretch_times(fp, points, size, 3.0);
    
    //normalize(fp, points, &size, 4.0);
   
    //shift_Up(fp, points, &size, 5.0);

    // shift_Down(fp, points, &size, 5.0);

    scale_by_factor(fp, points, &size, 2);
    
    printf("read %lu breakpoints\n", size);

    dur = points[size - 1].time;

    printf("duration: %f seconds\n", dur);

    point_to_Store = maxpoint(points, size);

    printf("maximum value: %f at %f secs\n", point_to_Store.value, point_to_Store.time);

    free(points);
    fclose(fp);

    return 0;
}

/* FUNCTIONS*/
BREAKPOINT *get_breakpoints(FILE *fp, unsigned long *psize)
{
    int got;                                // To handle the sscanf.
    unsigned long npoints = 0, size = 64;   // Initial size.
    TIME lasttime = 0.0;                    // To track the last time.
    BREAKPOINT *points = NULL;              // To make sure that the array is empty.
    char line[80];                          // To read each line of the FILE, max 80 characters.
    
    /* If the FILE is not opened. */
    if (fp == NULL)                         
        return NULL;
    /* Allocating space for points. */
    points = (BREAKPOINT *)malloc(sizeof(BREAKPOINT) * size);
    
    /* If does not have enough space. */
    if (points == NULL)
        return NULL;

    while (fgets(line, 80, fp))
    {
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);

        if (got < 0)
            continue;

        if (got == 0)
        {
            printf("Line %lu has non-numeric data\n", npoints + 1);
            break;
        }

        if (points[npoints].time < lasttime)
        {
            printf("data error at point %lu: time not increasing\n", npoints + 1);
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

BREAKPOINT maxpoint(const BREAKPOINT *points, unsigned long npoints)
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

/* New functions */
BREAKPOINT *stretch_times(FILE *fp, BREAKPOINT *points, unsigned long size, TIME timeFactor)
{
    fputs("\n////////////////////////////////\n", fp);
    fprintf(fp, "TimeStretch by a factor of %.1lfx:\n", timeFactor);

    for (int i = 0; i < size; i++)
    {
        points[i].time *= timeFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *normalize(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE normalFactor)
{
    BREAKPOINT maximumpoint;

    maximumpoint = maxpoint(points, *size);

    fprintf(fp, "\nNormalized by a factor of %lf:\n", normalFactor);
    fprintf(fp, "Every breakpoint reduced by %.1lf%%\n", ((maximumpoint.value - normalFactor) * 100) / maximumpoint.value);

    for (int i = 0; i < *size; i++)
    {
        points[i].value = normalFactor * (points[i].value / maximumpoint.value);
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *shift_Up(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor)
{
    fclose(fp);
    fp = fopen("breakb.txt", "w");
    //fprintf(fp, "\nShifted up by a factor of %.1lfx:\n", shiftFactor);

    for (int i = 0; i < *size; i++)
    {
        points[i].value += shiftFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *shift_Down(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor)
{
    fclose(fp);
    fp = fopen("breakb.txt", "w");

    //fprintf(fp, "\nShifted down by a factor of %.1lfx:\n", shiftFactor);

    for (int i = 0; i < *size; i++)
    {
        points[i].value -= shiftFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *scale_by_factor(FILE *fp, BREAKPOINT *points, unsigned long *size, unsigned long scaleFactor)
{
    BREAKPOINT *aux;
    BREAKPOINT *temp;
    TIME  auxTime;
    VALUE auxValue;
    int j = 0;
    int k = 0;
    int countGuard = 0;

    aux = (BREAKPOINT *)malloc(*size * sizeof(BREAKPOINT *)); 
    aux = points;
    temp = (BREAKPOINT *)realloc(points, ((*size) * scaleFactor) * sizeof(BREAKPOINT) + 1);
    points = temp;

    fputs("\n////////////////////////////////\n", fp);
    fprintf(fp, "Scale by a factor of %lux:\n", scaleFactor);

    for (int i = 0; i + 1 < *size; i++)
    {
        auxTime  = (aux[i + 1].time  - aux[i].time)  / (double)(scaleFactor + 1);
        auxValue = (aux[i + 1].value - aux[i].value) / (double)(scaleFactor + 1);

        if (auxValue < 0)
            auxValue = (aux[i].value - aux[i + 1].value) / (double)(scaleFactor + 1);

        for (j = countGuard, k = 0; k < scaleFactor + 1; j++, k++)
        {
            points[i + j].time  = aux[i].time  + auxTime  * (double)k;
            points[i + j].value = aux[i].value + auxValue * (double)k;

            fprintf(fp, "%lf %lf\n", points[i + j].time, points[i + j].value);
            countGuard++;
        }
    }

    free(temp);
    free(aux);

    return points;
}

int *insert_point(FILE *fp, BREAKPOINT p)
{
    fprintf(fp,"%lf %lf\n", p.time, p.value);

    return 0;
}

int *delete_point(FILE *fp,unsigned long *size, BREAKPOINT p)
{
    BREAKPOINT *points;
    
    points = get_breakpoints(fp, size);

    fputs("\n////////////////////////////////\n", fp);
    fputs("Deleted point\n", fp);
    for (int i = 0; i < *size; i++)
    {   
        if (points[i].time == p.time && points[i].value == p.value)
        {
            continue;
        }

        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return 0;
}
/*
    OUTPUTSAMPLE:
        textfile_content breakb.txt:
            0.0 1.23
            1.2 3.68
            4.6 2.11
            9.2 2.021

        input: 6-Listing1.7.4.c breakb.txt
        output:
            breakdur: find duration of breakpoint file
            read 4 breakpoints
            duration: 9.200000 seconds
            maximum value: 3.680000 at 1.200000 secs

*/