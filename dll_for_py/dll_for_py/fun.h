#pragma once
#include<fstream>
#include<math.h>

#define MAX_ARR 100
#define KRAT 5

using namespace std;

double f(double x, double v)
{
	return x + 3 * v + 5 * v;
}


void record(ostream* f, double * d, int max)
{
	for (int i = 1; i <= max; i++)
	{
		if ((i - 1) % 4 == 0)
			*f << "\n" << i / 4 + 1 << ":\t";
		*f << d[i - 1] << " ";
	}
}