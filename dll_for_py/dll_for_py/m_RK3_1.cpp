#include "stdafx.h"
#include"m_RK3_1.h"
#include"fun.h"

//данные предоставляют сплошной массив, поэтому для удобства я сделал набор типо понятных символов
//например чтобы обратиться к v1 элементу массива(по сути 2-й по счету) надо написать perem[__v1]
//																что равносильно perem[1]						
enum { __x, __v1, __e, __h1, __h2, __h3 };

#define EPS 0.01
#define P_PLUS_ODIN 4 

// j здесь для сдвига массива по __h, опять же для памяти и быстродействия
double st_RK_1(double* perem, double *k, int j)
{
	//_h = h / 2;
	perem[__h2 + j] = perem[__h1 + j]/2;
	//k[0] = f(x[0], v1[0]);
	k[0] = f(perem[__x], perem[__v1]);
	//k[1] = f(h / 2 + x[0], _h[0] *k[0] + v1);
	k[1] = f(perem[__h1 + j] / 2 + perem[__x], perem[__h2 + j] * k[0] + perem[__v1]);
	//k[2] = f(x + h, (-k + 2 * k)*h + v1);
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
	double k[3] = {};
	int z = 0;
	double tmp = 0.0;
	vector<double> d_v;
	double C[2] = {};

	string name = string(name_txt);
	ofstream _f(name);


	//инициализация массива
	perem[__x] = x;
	perem[__v1] = v1;
	perem[__e] = 0.0;
	perem[__h1] = h;
	perem[__h2] = 0.0;
	perem[__h3] = 0.0;

	//добавление в вектор 1-х значений
	d_v.push_back(perem[__x]);
	d_v.push_back(perem[__v1]);
	d_v.push_back(perem[__e]);
	d_v.push_back(perem[__h1]);

	for (int i = 0; perem[__x]<max_x && perem[__v1]<max_v; i++)
	{
		//вычисление 
		v_temp = st_RK_1(perem, k, 0);
		v2 = st_RK_1(perem, k, 1);

		perem[__e] = abs(perem[__v1] - v2);

		//условие, если рез функции зашел за наши параметры
		if (perem[__e] > EPS*pow(2, P_PLUS_ODIN))
		{
			i--;
			perem[__h1] = perem[__h1] / 2;
			C[1] += 1;
			continue;
		}

		if (perem[__e] < EPS)
		{
			perem[__h1] = perem[__h1] * 2;
			C[0] += 1;

		}

		//----------------------------------------------------------------------

		//пихаем значения и погрешность
		perem[__v1] = v_temp;

		//кидаем в вектор то что нужно
		d_v.push_back(perem[__x]);
		d_v.push_back(perem[__v1]);
		d_v.push_back(perem[__e]);
		d_v.push_back(perem[__h1]);


		//увеличиваем x
		perem[__x] += perem[__h1];
	}

	//собираем массив и кидаем в питон
	*py = new double[d_v.size()];
	std::memcpy(*py, d_v.data(), d_v.size() * sizeof d_v[0]);
	int size = d_v.size();

	//запись в файл
	record(&_f, *py, size);
	
	//возвращаем размер массива 
	return size;
}
