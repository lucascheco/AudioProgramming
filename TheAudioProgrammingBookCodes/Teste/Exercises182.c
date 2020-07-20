//Author: Lucas Pacheco.
//Description: Test exercise from "The Audio Programming Book", chapter 1, Exercises 1.8.2 .
//Date: 20/06/2020.

/* Not exponential Envelope */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    double attack_Duration, decay_Duration, level;
    double stepX, stepY;
    int points;
    FILE *fp;
    
    fp = fopen("ADenv.txt", "w");

    if (argc != 5)
    {
        fprintf(stderr, "usage: ADenv AttackDur DecayDur Level Points");
        return 1;
    }

    attack_Duration = atof(argv[1]);

    if (attack_Duration <= 0.0)
    {
        fprintf(stderr, "Error: Attack duration must be positive.\n");
        return 1;
    }

    decay_Duration = atof(argv[2]);

    if (decay_Duration <= 0.0)
    {
        fprintf(stderr, "Error: Decay duration must be positive.\n");
        return 1;
    }

    level = atof(argv[3]);

    if (level <= 0)
    {
        fprintf(stderr, "error: Level must be bigger than zero\n");
        return 1;
    } 
    
    points = atoi(argv[4]);

    if (points <= 0)
    {
        fprintf(stderr, "Error: points must be positive!\n");
        return 1;
    }
    
    stepX = attack_Duration / points;
    stepY = level / points;
    
    for (int i = 0; i <= points; i++)
    {
        fprintf(fp, "%lf %lf\n", stepX * (double)i, stepY * (double)i);
    }

    stepX = decay_Duration / points;
    stepY = level / points;

    for (int i = points, j = 0; i >= 0; i--, j++)
    {
        fprintf(fp, "%lf %lf\n", stepX * (double)j + attack_Duration, stepY * (double)i);
    }

    fclose(fp);
    return 0;
}