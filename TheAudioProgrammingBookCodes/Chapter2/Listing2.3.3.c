/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, Listing 2.3.1 .
    Date:        16/11/2021
************************************************************************************/

#include <portsf.h>

PANPOS constpower(double position) {
    PANPOS pos;
    const double piovr2 = 4.0 * atan(1.0) * 0.5;
    const double root2ovr2 = sqrt(2.0) * 0.5;

    double thispos = position * piovr2;
    double angle = thispos * 0.5;

    pos.left = root2ovr2 * (cos(angle) - sin(angle));
    pos.right = root2ovr2 * (cos(angle) + sin(angle));

    return pos;
}
