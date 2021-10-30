#pragma once
#include<math.h>

#define MAX_ARR 100
#define KRAT_ARR 8
#define g 9.81

using namespace std;

double f(double x, double v,double a1, double a3, double m)
{
	return - (a1 * v, + a3 * pow(v, 3)) / m;
}

double f1_11(double x, double v1, double v2)
{
	return v2;
}

double f2_11(double x, double v1, double v2, double k, double f, double m)
{
	return g * f - k * v1 / m;
}


void record(ostream* f, double * d, int max)
{
	for (int i = 1; i <= max; i++)
	{
		if ((i - 1) % KRAT_ARR == 0)
			*f << "\n" << i / KRAT_ARR + 1 << ":\t";
		*f << d[i - 1] << "\t";
	}
}