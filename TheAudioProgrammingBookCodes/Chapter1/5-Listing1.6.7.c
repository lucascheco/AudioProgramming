//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.7 .
//Date: 29/05/2020.

#include <stdio.h>

int main(int argc, char *argv[])
{
    char flag;
    int ismidi, write_interval, playit;

    if (argv[1][0] == '-')
    {
        flag = argv[1][1];

        if (flag == 'm')
            ismidi = 1;
        else if (flag == 'i')
            write_interval = 1;
        else if (flag == 'p')
            playit = 1;
        else
        {
            printf("error: incorrect flag option %s\n", argv[1]);
            return 1;
        }
    }

    return 0;
}