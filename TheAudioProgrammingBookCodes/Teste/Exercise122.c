//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", another cast exercise.
//Date: 09/05/2020.

#include <stdio.h>

int main()
{
    double fracsamp;
    short samp;

    fracsamp = 0.5;
    //The statement
    samp = (short)fracsamp * 32767;
    //is intended to convert a floating-point sample(+-1.0) to the 16-bit integer range:
    //However the output is not as expected. Why?

    //ANSWER: The precedence is of the casting and not from multiplication, so "fracsamp = 0" multiplied by 32767 is 0.
    //         We need to use parentheses to specify the entire expression => "samp = (short)(fracsamp * 32767);"

    printf("%i\n", samp);
    return 0;
}

/*
    OUTPUT SAMPLE:
        0
*/