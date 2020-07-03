#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileMenu.h"

FILE *menu_mode(FILE *fp, const char *filename, flagOption *flag)
{
    char *op;
    op = (char *)malloc(sizeof(char *));

    printf("Select a type: \n");
    printf("r\\ w\\ r+\\ w+\\ a\\ a+\n");

    gets(op);

    if (strcmp(op, "r") == 0)
    {
        fp = fopen(filename, "r");
        *flag = 1;
    }
    else if (strcmp(op, "w") == 0)
    {
        fp = fopen(filename, "w");
        *flag = 2;
    }
    else if (strcmp(op, "r+") == 0)
    {
        fp = fopen(filename, "r+");
        *flag = 3;
    }
    else if (strcmp(op, "w+") == 0)
    {
        fp = fopen(filename, "w+");
        *flag = 4;
    }
    else if (strcmp(op, "a") == 0)
    {
        fp = fopen(filename, "a");
        *flag = 5;
    }
    else if (strcmp(op, "a+") == 0)
    {
        fp = fopen(filename, "a+");
        *flag = 6;
    }
    else
    {
        printf("Invalid option on FILE MENU.\n");
        *flag = 0;
        return NULL;
    }
    
    free(op);
    return fp;
}

void menu_option()
{
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
}