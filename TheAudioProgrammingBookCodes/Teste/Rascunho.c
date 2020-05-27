//Author: Lucas Pacheco.
//Description: A program for testing, this code always will be changed.
//Date: 26/05/2020.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    double buffer[1024];
    double *ptr = buffer;

    for (int i = 0; i < 1024; i++)
    {
        *ptr++ = 0.0;
    }

    for (int i = 0; i < 1024; i++)
    {
        printf("%lf\n", buffer[i]);
    }

    return 0;
}