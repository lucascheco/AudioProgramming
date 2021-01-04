/***********************************************************************************
    Author: Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.9 .
    Date: 29/05/2020.
************************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
    float buffer[1024];
    float *bufptr = buffer;
    int ascending = 0;

    if (ascending)
    {
        int i;

        for (i = 0; i < 1024; i++)
            *bufptr++ = (float)i;
    }
    else
    {
        int i;

        for (i = 1024; i; i--)
            *bufptr++ = (float)i;
    }

    return 0;
}