// dll_for_py.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


// test.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <string.h>
#include<iostream>
#include <vector>
#include <cstring>
#include<fstream>
#include<string>
#include <math.h>

using namespace std;

#define MAX_ARR 100
#define KRAT 5


enum { __x, __v1, __e, __h1,__h2,__h3 };

//Общие функции-----------------------------------------------------------------------------------------------
double f(double x, double v)
{
	return x + 3 * v + 5 * v;
}
//функция записи в файл, _i - номер 1-го результата, z - размер массивов
void record(ostream* f, double * d, int max)
{
	for (int i = 1; i <= max; i++)
	{
		if ((i - 1) % 4 == 0 )
			*f << "\n" << i / 4 + 1 << ":\t";
		*f << d[i - 1] << " ";
	}
}

//метод РК 3(1) с Записью в текстовый файлик, нач усл - x,h,v1; name_txt - как будет называться файлик. (пример test.txt)
int m_RK3_1_r(double x, double v1, double h, double max_x, double max_v, char* name_txt, double** py);



extern "C" __declspec(dllexport) void __stdcall work_RK31R(double** data, double * d, double * max, int* _i)
{

	*_i = m_RK3_1_r(d[0], d[1], d[2], max[0], max[1], "test1.txt", data);
}



//Функции для конкретного метода-------------------------------------------------------------------------------

double st_RK_1(double* perem,double *k,int j)
{
	//_h = h / 2;
	perem[__h2 + j] = perem[__h1 + j];
	//k[0] = f(x[0], v1[0]);
	k[0] = f(perem[__x], perem[__v1]);
	//k[1] = f(h[0] / 2 + x[0], _h[0] *k[0] + v1[0]);
	k[1] = f(perem[__h1 + j] / 2 + perem[__x], perem[__h2 + j] * k[0] + perem[__v1]);
	//k[2] = f(x[0] + h[0], (-k[0] + 2 * k[1])*h[0] + v1[0]);
	k[2] = f(perem[__x] + perem[__h1 + j], (-k[0] + 2 * k[1])*perem[__h1 + j] + perem[__v1]);

	//return (k[0] + 4 * k[1] + k[2]) / 6 *(*h) + (*v1);
	return (k[0] + 4 * k[1] + k[2]) / 6 * perem[__h1 + j] + perem[__v1];
}

int m_RK3_1_r(double x, double v1, double h, double max_x, double max_v, char* name_txt, double** py)
{
	double v_temp = 0.0;
	double v2 = 0.0;
	//------------------x---v1---e---h
	double perem[6] = {};
	double rec[MAX_ARR * 5] = {};
	double k[3] = {};
	int z = 0;
	int _i = 0;
	vector<double> d_v;

	string name = string(name_txt);
	ofstream _f(name);



	perem[__x] = x;
	perem[__v1] = v1;
	perem[__e] = 0.0;
	perem[__h1] = h;
	perem[__h2] = 0.0;
	perem[__h3] = 0.0;

	d_v.push_back(perem[__x]);
	d_v.push_back(perem[__v1]);
	d_v.push_back(perem[__e]);
	d_v.push_back(perem[__h1]);

	for (int i = 0; perem[__x]<max_x && perem[__v1]<max_v; i++)
	{

		v_temp = st_RK_1(perem, k, 0);
		v2 = st_RK_1(perem, k, 1);

		if (v_temp - perem[__v1] > 0.5 || perem[__v1] - v_temp > 0.5)
		{
			i--;
			perem[__h1] = perem[__h1] / 2;
			continue;
		}

		if (v_temp - perem[__v1] < 0.1 && perem[__v1] - v_temp < 0.1)
		{
			perem[__h1] = perem[__h1] * 2;
		}

		perem[__v1] = v_temp;
		perem[__e] = abs(perem[__v1] - v2);


		d_v.push_back(perem[__x]);
		d_v.push_back(perem[__v1]);
		d_v.push_back(perem[__e]);
		d_v.push_back(perem[__h1]);



		perem[__x] += perem[__h1];
	}

	*py = new double[d_v.size()];
	std::memcpy(*py, d_v.data(), d_v.size() * sizeof d_v[0]);
	int size = d_v.size();
	record(&_f, *py, size);

	return size;
}
