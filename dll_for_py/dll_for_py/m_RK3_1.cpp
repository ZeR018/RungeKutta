#include "stdafx.h"
#include"m_RK3_1.h"
#include"fun.h"

//������ ������������� �������� ������, ������� ��� �������� � ������ ����� ���� �������� ��������
//�������� ����� ���������� � v1 �������� �������(�� ���� 2-� �� �����) ���� �������� perem[__v1]
//																��� ����������� perem[1]						
enum { __x, __v1, __e, __h1, __h2, __h3 };

#define NOT_MORE 0.5
#define NOT_SMOL 0.1

// j ����� ��� ������ ������� �� __h, ����� �� ��� ������ � ��������������
double st_RK_1(double* perem, double *k, int j)
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
	double tmp = 0.0;
	vector<double> d_v;

	string name = string(name_txt);
	ofstream _f(name);


	//������������� �������
	perem[__x] = x;
	perem[__v1] = v1;
	perem[__e] = 0.0;
	perem[__h1] = h;
	perem[__h2] = 0.0;
	perem[__h3] = 0.0;

	//���������� � ������ 1-� ��������
	d_v.push_back(perem[__x]);
	d_v.push_back(perem[__v1]);
	d_v.push_back(perem[__e]);
	d_v.push_back(perem[__h1]);

	for (int i = 0; perem[__x]<max_x && perem[__v1]<max_v; i++)
	{
		//���������� 
		v_temp = st_RK_1(perem, k, 0);
		v2 = st_RK_1(perem, k, 1);

		//�������, ���� ��� ������� ����� �� ���� ���������
		if (v_temp - perem[__v1] > NOT_MORE || perem[__v1] - v_temp > NOT_MORE)
		{
			i--;
			perem[__h1] = perem[__h1] / 2;
			continue;
		}

		if (v_temp - perem[__v1] < NOT_SMOL && perem[__v1] - v_temp < NOT_SMOL)
		{
			perem[__h1] = perem[__h1] * 2;
		}
		//----------------------------------------------------------------------

		//������ �������� � �����������
		perem[__v1] = v_temp;
		tmp = perem[__v1] - v2;
		if (tmp < 0)
			perem[__e] = tmp*(-1);
		else
			perem[__e] = tmp;
		//perem[__e] = abs(perem[__v1] - v2);

		//������ � ������ �� ��� �����
		d_v.push_back(perem[__x]);
		d_v.push_back(perem[__v1]);
		d_v.push_back(perem[__e]);
		d_v.push_back(perem[__h1]);


		//����������� x
		perem[__x] += perem[__h1];
	}

	//�������� ������ � ������ � �����
	*py = new double[d_v.size()];
	std::memcpy(*py, d_v.data(), d_v.size() * sizeof d_v[0]);
	int size = d_v.size();
	//������ � ����
	record(&_f, *py, size);
	
	//���������� ������ ������� 
	return size;
}
