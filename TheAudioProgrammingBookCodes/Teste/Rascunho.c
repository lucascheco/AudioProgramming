//Author: Lucas Pacheco.
//Description: A program for testing, this code always will be changed.
//Date: 26/05/2020.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileMenu.c"
int main()
{
    FILE *fp;
    flagOption *flag;
    char myfile[] = "myfile.txt";
    char *text;
    text = (char *)malloc(sizeof(char *));

    flag = (flagOption *)malloc(sizeof(flagOption *));
    fp = menu_mode(fp, myfile, flag);

    if (*flag == 1)
    {
        printf("ReadMode: \n");
        sscanf(80, "%s", text);
        }
    else if (*flag == 2)
    {
        printf("WriteMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "\n%s", text);
    }
    else if (*flag == 3)
    {
    }
    else if (*flag == 4)
    {
    }
    else if (*flag == 5)
    {
    }
    else if (*flag == 6)
    {
    }
    else
    {
        printf("Invalid option\n");
    }

    free(text);
    fclose(fp);
    return 0;
}