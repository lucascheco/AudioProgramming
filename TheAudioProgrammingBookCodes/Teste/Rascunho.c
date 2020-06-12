//Author: Lucas Pacheco.
//Description: A program for testing, this code always will be changed.
//Date: 26/05/2020.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;

    for (i = 0; i < 10;)
    {
        if (i++ % 2 == 0)
            printf("%d\n", i);
    }

    return 0;
}