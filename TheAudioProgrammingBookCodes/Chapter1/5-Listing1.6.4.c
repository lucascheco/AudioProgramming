//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.4 .
//Date: 29/05/2020.

#include <stdio.h>

int main(int argc, char *argv[])
{
    int ismidi, write_interval;

    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'm')
            ismidi = 1;
        else if (argv[1][1] == 'i')
            write_interval = 1;
        else
        {
            printf("error: incorret flag option %s\n", argv[1]);
            return 1;
        }
    }

    return 0;
}