/*
    Author: Lucas Pacheco.
    Description: A copy from "The Audio Programming Book", chapter 0, Pointers to functions example.
    Date: 15/12/2020.
*/

#include <stdio.h>

/* How many times do you want to print the message, the type of message(IMPORNTANT, WARNING, ERROR and etc), the message. */
void message_printer(int times, void (*callback)(char *msg), char *user_mess)
{
    int i;
    for (i = 0; i < times; i++)
        callback(user_mess);
}

/* A important message. */
void my_important_message(char *mess)
{
    printf("VERY IMPORTANT: %s\n", mess);
}

/* A warning message. */
void my_warning_message(char *mess)
{
    printf("WARNING: %s\n", mess);
}

int main()
{
    message_printer(10, my_important_message, "functions can be pointers");
    message_printer(1,  my_warning_message, "but be careful");
    return 0;
}