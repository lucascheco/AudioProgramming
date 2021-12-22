/***********************************************************************************************
    Author: Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", chapter 1, Exercises 1.8.1 .
    Date: 20/06/2020.
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
	
const double samplerate = 44100;
double coeff;
double currentLevel;

void init(double levelBegin, double levelEnd, float releaseTime)
{
    currentLevel = levelBegin;

    coeff = (log(levelEnd) - log(levelBegin)) / (releaseTime * samplerate);
}

void calculateEnvelope(int samplePoints, FILE *fp)
{
    for (int i = 0; i < samplePoints; i++)
    {
        fprintf(fp, "%lf %lf\n", (double)i, currentLevel);
        fprintf(stdout, "%lf %lf\n", (double)i, currentLevel);
        currentLevel += coeff * currentLevel;
    }
}

int main()
{
    FILE *fp;

    fp = fopen("Env.txt", "w");
    init(1.0, 0.0001, 10.0);
    //printf("%.10lf\n", coeff);
    calculateEnvelope(30, fp);
    
    fclose(fp);
    return 0;
}