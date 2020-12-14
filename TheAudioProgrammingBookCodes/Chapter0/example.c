#include <stdio.h>

int main()
{
    for (int fahr = 0; fahr <= 300; fahr++)
        printf("%4d %6.1f\n", fahr, (5.0 / 9.0)*(fahr - 32));

    return 0;
}