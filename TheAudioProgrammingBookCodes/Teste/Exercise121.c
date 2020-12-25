/*
    Author: Lucas Pacheco.
    Description: A test exercise from "The Audio Programming Book", about sizeof().
    Date: 09/05/2020.
*/

#include <stdio.h>

int main()
{
    printf("int    size %ld.\n", sizeof(int));
    printf("char   size %ld.\n", sizeof(char));
    printf("short  size %ld.\n", sizeof(short));
    printf("long   size %ld.\n", sizeof(long));
    printf("float  size %ld.\n", sizeof(float));
    printf("double size %ld.\n", sizeof(double));

    return 0;
}

/*
    OUTPUT SAMPLE:
        int    size 4.
        char   size 1.
        short  size 2.
        long   size 8.
        float  size 4.
        double size 8.
*/