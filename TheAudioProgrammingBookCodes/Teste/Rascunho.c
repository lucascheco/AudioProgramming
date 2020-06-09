//Author: Lucas Pacheco.
//Description: A program for testing, this code always will be changed.
//Date: 26/05/2020.

#include <stdio.h>
#include <stdlib.h>
#define max 100
// #define TIME double
// #define VALUE double

typedef double TIME;
typedef double VALUE;
typedef struct breakpoint
{
    TIME time;
    VALUE value;
} BREAKPOINT;

struct breakpoint c;

int main()
{
    BREAKPOINT a = {2.232, 8.4054};
    BREAKPOINT b;

    b = a;
    c = b;

    printf("a time: %lf\n", a.time);
    printf("a value: %lf\n", a.value);

    printf("b time: %2.2lf\n", b.time);
    printf("b value: %2.2lf\n", b.value);

    printf("c time: %2.2lf\n", c.time + 3.9021);
    printf("c value: %2.2lf\n", c.value + 6.128);

    return 0;
}