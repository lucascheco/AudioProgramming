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
    char myfile[] = "breakb.txt";
    char *text;
    text = (char *)malloc(sizeof(char *));

    flag = (flagOption *)malloc(sizeof(flagOption *));
    fp = menu_mode(fp, myfile, flag);

    if (*flag == 1)
    {
        printf("ReadMode: \n");

        char c;

        while ((c = fgetc(fp)) != EOF)
            printf("%c", c);
    }
    else if (*flag == 2)
    {
        double n1, n2;
        printf("WriteMode: \n");
        printf("Type a new text: ");
        scanf("%lf", &n2);
        for (int i = 0; i < 100; i++)
        {
            fprintf(fp, "%f %lf\n", (double)i, n2 * ((double)i / 2));
        }
    }
    else if (*flag == 3)
    {
        printf("Read_and_WriteMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "\n%s", text);
    }
    else if (*flag == 4)
    {
        printf("Read_and_WriteMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "\n%s", text);
    }
    else if (*flag == 5)
    {
        printf("AppendMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "\n%s", text);
    }
    else if (*flag == 6)
    {
        printf("Append_and_ReadMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "\n%s", text);
    }
    else
    {
        printf("Invalid option\n");
    }

    free(text);
    fclose(fp);
    return 0;
}