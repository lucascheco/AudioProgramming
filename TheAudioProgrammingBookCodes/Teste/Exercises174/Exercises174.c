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
TIME last_Time(const BREAKPOINT *points, unsigned long npoints);

int number_of_breakpoints(const BREAKPOINT *points);

BREAKPOINT *stretch_times(FILE *fp, BREAKPOINT *points, unsigned long size, TIME timeFactor);

BREAKPOINT *normalize(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE normalFactor);

BREAKPOINT *shift_Up(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor);

BREAKPOINT *shift_Down(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor);

BREAKPOINT *scale_by_factor(FILE *fp, BREAKPOINT *points, unsigned long scaleFactor);

BREAKPOINT *truncate(FILE *fp, unsigned long *size);

BREAKPOINT *extend(FILE *fp, unsigned long *size);

int insert_point(FILE *fp, BREAKPOINT *points, BREAKPOINT p);

int delete_point(FILE *fp, BREAKPOINT *points, BREAKPOINT p);

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
    
    to_add.time = 0.000000; 
    to_add.value = 4.000000;
    
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

    printf("O numero de breakpoints %d\n", number_of_breakpoints(points));

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
   
    // insert_point(fp, points, to_add);

    // delete_point(fp, points, to_add);
    
    stretch_times(fp, points, size, 3.0);
    
    // normalize(fp, points, &size, 10.0);
   
    // shift_Up(fp, points, &size, 5.0);

    // shift_Down(fp, points, &size, 5.0);

    // scale_by_factor(fp, points, 2);
    
    printf("read %lu breakpoints\n", size);

    dur = points[size - 1].time;

    printf("duration: %f seconds\n", dur);

    point_to_Store = maxpoint(points, size);

    printf("maximum value: %f at %f secs\n", point_to_Store.value, point_to_Store.time);

    free(points);
    fclose(fp);

    return 0;
}

/* FUNCTIONS */
BREAKPOINT *get_breakpoints(FILE *fp, unsigned long *psize)
{
    /* 
        On function parameters we pass the FILE where the breakpoints are,
        and when we want to return more than one value, we pass the "psize"
        parameter where it will change the variable that you passed and return
        the size or the number of breakpoints.
    */
    int got;                                // To handle the sscanf.
    unsigned long npoints = 0, size = 64;   // A counter "npoints" and a initial size.
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

    /* fgets => get the data from the FILE to the line variable */
    /*
        I believe when is reached the end of FILE the "while" breaks or when a condition on if
        statements is true.
    */
    while (fgets(line, 80, fp))
    {
        /* To handle error we store the sscanf output to variable "got". */
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);

        if (got < 0)
            continue;

        if (got == 0)
        {
            printf("Line %lu has non-numeric data\n", npoints + 1);
            break;
        }

        /* 
            Time needs to increase. So "points[i].time < lasttime" or 
            "points[i].time < points[i + 1].time". 
        */
        if (points[npoints].time < lasttime)
        {
            printf("data error at point %lu: time not increasing\n", npoints + 1);
            break;
        }
        /* To store lasttime. */
        lasttime = points[npoints].time;
        
        /* 
            Now we increment "npoints" and compare with initial size,
            if reached the size we realloc more memory to the "points".
        */
        if (++npoints == size)
        {
            BREAKPOINT *temp;
            /* "size" = 64 + 64 */
            size += npoints;

            /* We store to a "temp" variable to handle error and expand "npoints" size. */
            temp = (BREAKPOINT *)realloc(points, sizeof(BREAKPOINT) * size);
            
            /* If not enough memory, is safer to "free" "npoints" and set it to "NULL". */
            if (temp == NULL)
            {
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }

            /* "npoints" = extension. */
            points = temp;
        }
    }

    /* 
        If not enough memory ro realloc we set "npoints" to zero and this if statement 
        will not be triggered. The "psize" reference will not be changed.
    */
    if (npoints)
        *psize = npoints;
    
    // We return the "points" read from the FILE.
    return points;
}

BREAKPOINT maxpoint(const BREAKPOINT *points, unsigned long npoints)
{
    /* On function parameters we pass the array of points and its size. */
    int i; // A counter for the for loop.
    BREAKPOINT point; // A aux variable to store the maxpoint.

    // To initialize the point variable with the initial value of the array.
    point.time = points[0].time; 
    point.value = points[0].value;

    /*
        This will compare each breakpoint from the array and store the biggest to
        the "point" variable.
    */
    for (i = 0; i < npoints; i++)
    {
        if (points[i].value > point.value)
        {
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }

    // Return the biggest.
    return point;
}

/* New functions */

TIME last_Time(const BREAKPOINT *points, unsigned long npoints)
{
    return points[npoints - 1].time;
}

int number_of_breakpoints(const BREAKPOINT *points)
{
    int i = 0;

    while (points[i].time < points[i + 1].time)
        i++;
    
    if(i == 0)
        return 0;   
    else
        return i + 1;
}

BREAKPOINT *stretch_times(FILE *fp, BREAKPOINT *points, unsigned long size, TIME timeFactor)
{
    // For instance I do not want to override the breakpoints or create new files.
    // Just append some text, and the breakpoints changes.
    /*
        On function parameter we pass:
            -FILE: to append the data.
            -Breakpoints array: to modify.
            -The size: to simplify the function.
            -Timefactor: the how long or short do you want to stretch.
    */
    fputs("\n////////////////////////////////\n", fp);
    fprintf(fp, "TimeStretch by a factor of %.1lfx:\n", timeFactor);
    
    /* We just multiply the time by the factor. */
    for (int i = 0; i < size; i++)
    {
        points[i].time *= timeFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *normalize(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE normalFactor)
{
    /*
        On function parameter we pass:
            -FILE: to append the data.
            -Breakpoints array: to modify.
            -The size: to simplify the function.
            -Normalfactor: what value of reference.
    */

    BREAKPOINT maximumpoint; // To store the maximum point we use the maxpoint function.

    maximumpoint = maxpoint(points, *size); 

    fprintf(fp, "\nNormalized by a factor of %lf:\n", normalFactor);

    /* This expression on "fprintf" translate to percentage the value that will be normalized. */
    /*
        dif --- x    ---> x = (dif * 100) / max
        max --- 100  ---> x = expression
    */
    if ((maximumpoint.value - normalFactor) > 0)
        fprintf(fp, "Every breakpoint reduced by %.1lf%%\n", ((maximumpoint.value - normalFactor) * 100) / maximumpoint.value);
    else
        fprintf(fp, "Every breakpoint increased by %.1lf%%\n", ((normalFactor - maximumpoint.value) * 100) / maximumpoint.value);
    
    for (int i = 0; i < *size; i++)
    {
        /* Here we reduce every breakpoint by equaly amount. */
        points[i].value = normalFactor * (points[i].value / maximumpoint.value);
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *shift_Up(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor)
{
    /*
        On function parameter we pass:
            -FILE: to append the data.
            -Breakpoints array: to modify.
            -The size: to simplify the function.
            -shiftfactor: what value do you want to shiftup all values.
    */
    fprintf(fp, "\nShifted up by a factor of %.1lfx:\n", shiftFactor);

    for (int i = 0; i < *size; i++)
    {
        points[i].value += shiftFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *shift_Down(FILE *fp, BREAKPOINT *points, unsigned long *size, VALUE shiftFactor)
{
    /*
        On function parameter we pass:
            -FILE: to append the data.
            -Breakpoints array: to modify.
            -The size: to simplify the function.
            -shiftfactor: what value do you want to shiftdown all values.
    */
    fprintf(fp, "\nShifted down by a factor of %.1lfx:\n", shiftFactor);

    for (int i = 0; i < *size; i++)
    {
        points[i].value -= shiftFactor;
        fprintf(fp, "%lf %lf\n", points[i].time, points[i].value);
    }

    return points;
}

BREAKPOINT *scale_by_factor(FILE *fp, BREAKPOINT *points, unsigned long scaleFactor)
{
    TIME  auxTime;
    VALUE auxValue;
    int k = 0; 
    int size;

    size = number_of_breakpoints(points);
    
    fputs("\n////////////////////////////////\n", fp);
    fprintf(fp, "Scale by a factor of %lux:\n", scaleFactor);

    for (int i = 1; i < size; i++)
    {
        auxTime  = (points[i].time  - points[i - 1].time)  / (double)(scaleFactor + 1);
        auxValue = (points[i].value - points[i - 1].value) / (double)(scaleFactor + 1);

        // if (auxValue < 0)
        //     auxValue = (points[i - 1].value - points[i].value) / (double)(scaleFactor + 1);
 
        for (k = 0; k <= scaleFactor; k++)
        { 
            fprintf(fp, "%lf %lf\n", points[i - 1].time  + auxTime  * (double)k, points[i - 1].value + auxValue * (double)k);
        }
    }

    fprintf(fp, "%lf %lf\n", points[size - 1].time, points[size - 1].value);
    
    return points;
}

int insert_point(FILE *fp, BREAKPOINT *points, BREAKPOINT p)
{ 
    TIME lastTime;
    lastTime = last_Time(points, number_of_breakpoints(points));
    fclose(fp);
    fp = fopen("breakb.txt", "a");
    
    if (p.time < lastTime)
    {
        printf("Time needs to increase!\n");
        return 1;
    }
    else
    {      
        fprintf(fp,"\n%lf %lf", p.time, p.value);

        return 0;         
    }

}

int delete_point(FILE *fp, BREAKPOINT *points, BREAKPOINT p)
{
    int size;
    size = number_of_breakpoints(points);

    fputs("\n////////////////////////////////\n", fp);
    fputs("Deleted point\n", fp);
    for (int i = 0; i < size; i++)
    {   
        /* When we find the breakpoint, we do not print it. */
        if (points[i].time == p.time && points[i].value == p.value)    
            continue;

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