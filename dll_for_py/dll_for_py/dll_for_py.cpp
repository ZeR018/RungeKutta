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

using namespace std;

#define MAX_ARR 100

//Общие функции-----------------------------------------------------------------------------------------------
double f(double x, double v)
{
	return x + 3 * v + 5 * v;
}
//функция записи в файл, _i - номер 1-го результата, z - размер массивов
void record(ostream* f, int _i, int z, double*x, double* d, double *h)
{
	for (int i = 1; i <= z; i++)
	{
		*f << _i + i << "\t" << x[i - 1] << "\t" << d[i - 1] << "\t" << h[i - 1] << "\n";
	}
}

//метод РК 3(1) с Записью в текстовый файлик, нач усл - x,h,v1; name_txt - как будет называться файлик. (пример test.txt)
int m_RK3_1_r(double x, double v1, double h, double max_x, double max_v, char* name_txt, double** py);



//////extern "C" __declspec(dllexport) void __stdcall new_mem(unsigned char** p, int* s)
//extern "C" __declspec(dllexport) void __stdcall new_mem(int** p)
//{
//	*p = new int[3];
//	for (int i = 0; i < 3; i++)
//		(*p)[i] = i;
//	//ppMem = new int[*pSize];
//	//	ppMem[i] = i;
//}
//
//extern "C" __declspec(dllexport) void __stdcall test_vect(double* data)
//{
//	std::vector < double> v = { 4.5, 2.4, 5.5 };
//	//data = new double[v.size()];
//	std::memcpy(data, v.data(), v.size() * sizeof v[0]);
//}
//
//extern "C" __declspec(dllexport) void __stdcall fin_vect(double** data, int* _i, double * d)
//{
//	std::vector < double> v = { 4.4, 2.5, 5.3 };
//	*data = new double[v.size()];
//	std::memcpy(*data, v.data(), v.size() * sizeof v[0]);
//	for (int i = 0; i < 2; i++)
//	{
//		std::cout << _i[i] << "\n";
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		std::cout << d[i] << "\n";
//	}
//}


extern "C" __declspec(dllexport) void __stdcall work_RK31R(double** data, double * d, double * max, int* _i)
{

	*_i = m_RK3_1_r(d[0], d[1], d[2], max[0], max[1], "test1.txt", data);
}


//Функции для конкретного метода-------------------------------------------------------------------------------
int m_RK3_1_r(double x, double v1, double h, double max_x, double max_v, char* name_txt, double** py)
{
	double v2 = 0.0;
	double _h = 0.0;
	double tmp = 0.0;
	double d[MAX_ARR] = {};
	double _x[MAX_ARR] = {};
	double hh[MAX_ARR] = {};
	int z = 0;
	int _i = 0;
	vector<double> d_v;

	string name = string(name_txt);
	ofstream _f(name);

	for (int i = 0; x<max_x && v1<max_v; i++)
	{
		_h = h / 2;
		double k1 = f(x, v1);
		double k2 = f(h / 2 + x, _h*k1 + v1);
		double k3 = f(x + h, (-k1 + 2 * k2)*h + v1);
		tmp = (k1 + 4 * k2 + k3) / 6;
		v2 = tmp*h + v1;
		if (v2 - v1 > 0.5 || v1 - v2 > 0.5)
		{
			i--;
			h = h / 2;
			continue;
		}

		if (v2 - v1 < 0.1 && v1 - v2 < 0.1)
		{
			h = h * 2;
		}
		v1 = v2;
		d[z] = v1;
		_x[z] = x;
		hh[z] = h;

		d_v.push_back(x);
		d_v.push_back(v1);
		d_v.push_back(h);


		z++;
		if (z >= 100)
		{
			record(&_f, _i, z, _x, d, hh);
			z = 0;
			_i = i;
		}
		//cout << "x:   " << x << "\tv:" << v1 << "\ti:" << i << "\th:" << h << endl;
		x += h;
	}
	record(&_f, _i, z, _x, d, hh);

	*py = new double[d_v.size()];
	std::memcpy(*py, d_v.data(), d_v.size() * sizeof d_v[0]);
	int size = d_v.size();
	return size;
}




