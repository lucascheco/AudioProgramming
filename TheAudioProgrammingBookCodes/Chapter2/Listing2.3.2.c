/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, Listing 2.3.2 .
    Date:        21/01/2021
************************************************************************************/
#include <breakpoints.h>

double val_at_brktime(const BREAKPOINT* points, unsigned long npoints, double time)
{
    unsigned long i;
    BREAKPOINT left, right;
    double frac, val, width;

    /* scan until we find a span containing our time */
    for (i = 1; i < npoints; i++)
    {
        if (time <= points[i].time)
            break;
    }

    /* maintain final value if time beyond end of data */
    if (i == npoints)
    {
        return points[i - 1].value;
    }

    left  = points[i - 1];
    right = points[i];

    /* check for instant jump - two points with same time */
    width = right.time - left.time;
    if (width == 0.0)
        return right.value;

    /* get value from this span using linear interpolation */
    frac = (time - left.time) /  width;
    val = left.value + ((right.value - left.value) * frac);

    return val;
}