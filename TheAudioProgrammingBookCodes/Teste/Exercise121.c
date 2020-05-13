//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", about sizeof().
//Date: 09/05/2020.

#include <stdio.h>

int main()
{
    printf("int size %d.\n", sizeof(int));
    printf("char size %d.\n", sizeof(char));
    printf("short size %d.\n", sizeof(short));
    printf("long size %d.\n", sizeof(long));
    printf("float size %d.\n", sizeof(float));
    printf("double size %d.\n", sizeof(double));

    return 0;
}

/*
    OUTPUT SAMPLE:
        int size 4.
        char size 1.
        shor size 2.
        long size 4.
        float size 4.
        double size 8.
*/