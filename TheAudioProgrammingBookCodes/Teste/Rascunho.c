/*************************************************************************
    Author: Lucas Pacheco.
    Description: A program for testing, this code always will be changed.
    Date: 26/05/2020.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileMenu.c"
int main()
{
    FILE *fp;
    flagOption *flag;
    char myfile[] = "myfile.txt";

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
        char *text;
        text = (char *)malloc(99 * sizeof(char *));
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "%s\n", text);
        free(text);
                
    }
    else if (*flag == 3)
    {
        int op;

        printf("Read_and_WriteMode: \n");
        printf("1-Read 2- Write:\n");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                printf("ReadMode: \n");

                char c;

                while ((c = fgetc(fp)) != EOF)
                    printf("%c", c);
                
                break;

            case 2: 
            {
                char *text;
                text = (char *)malloc(99 * sizeof(char *));
            
                printf("Type a new text without a space a 99 char max: ");
                getchar();
                gets(text);
                fprintf(fp, "%s\n", text);
                free(text);
            }
                break;
            
            default:
                printf("Invalid mode.\n");
                break;
        }
    }
    else if (*flag == 4)
    {
        int op;

        printf("Write_and_ReadMode: \n");
        printf("1-Read 2- Write:\n");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                printf("ReadMode: \n");

                char c;

                while ((c = fgetc(fp)) != EOF)
                    printf("%c", c);
                
                break;

            case 2: 
            {
                char *text;
                text = (char *)malloc(99 * sizeof(char *));

                printf("Type a new text without a space a 99 char max: ");
                getchar();
                gets(text);
                fprintf(fp, "%s\n", text);
                free(text);
            }
                break;
            
            default:
                printf("Invalid mode.\n");
                break;
        }
    }
    else if (*flag == 5)
    {
        char *text;
        text = (char *)malloc(99 * sizeof(char *));

        printf("AppendMode: \n");
        printf("Type a new text: ");
        gets(text);
        fprintf(fp, "%s\n", text);
        free(text);
    }
    else if (*flag == 6)
    {
        int op;
        printf("Append_and_ReadMode: \n");
        printf("1-Append 2-Read:\n");
        scanf("%d", &op);
        
        switch(op)
        {
            case 1:
            {
                char *text;
                text = (char *)malloc(99 * sizeof(char *));
                
                printf("AppendMode: \n");
                printf("Type a new text: ");
                getchar();
                gets(text);
                fprintf(fp, "%s\n", text);
                free(text);
            }
                break;

            case 2:
                printf("ReadMode: \n");

                char c;

                while ((c = fgetc(fp)) != EOF)
                    printf("%c", c);
                
                break;

            default:
                printf("Invalid mode.\n");
                break;
        }
    }
    else
    {
        printf("Invalid option on Main.\n");
    }

    free(flag);

    fclose(fp);
    return 0;
}