#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *message;

    if (gets(message) == NULL)
    {
        printf("erro vazio\n");
        return 1;
    }

    return 0;
}