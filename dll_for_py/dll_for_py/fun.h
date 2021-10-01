#pragma once
#include<fstream>
#include<math.h>

#define MAX_ARR 100
#define KRAT 5
#define m 1
#define a1 1
#define a3 1

using namespace std;

double f(double x, double v)
{
	return - (a1 * v, + a3 * pow(v, 3)) / m;
}


void record(ostream* f, double * d, int max)
{
	for (int i = 1; i <= max; i++)
	{
		if ((i - 1) % 4 == 0)
			*f << "\n" << i / 6 + 1 << ":\t";
		*f << d[i - 1] << " ";
	}
}