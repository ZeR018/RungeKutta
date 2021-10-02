#include "stdafx.h"
#include"m_RK3_1.h"
#include"fun.h"

//������ ������������� �������� ������, ������� ��� �������� � ������ ����� ���� �������� ��������
//�������� ����� ���������� � v1 �������� �������(�� ���� 2-� �� �����) ���� �������� perem[__v1]
//																��� ����������� perem[1]						
enum { __x, __v1, __s, __h1, __h2, __h3, __u, __E,__c1,__c2 };
enum {__x0,__v0,__h0,__a1,__a3,__m,__e,__max_step, __gran};
enum {_x_u, __contr_e};

#define EPS 0.01
#define P 3
#define P_SIZE 10

// j ����� ��� ������ ������� �� __h, ����� �� ��� ������ � ��������������
double st_RK_1(double* perem,double* start_p, double *k, int j)
{
	//_h = h / 2;
	perem[__h2 + j] = perem[__h1 + j]/2;
	//k[0] = f(x[0], v1[0]);
	k[0] = f(perem[__x], perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
	//k[1] = f(h / 2 + x[0], _h[0] *k[0] + v1);
	k[1] = f(perem[__h1 + j] / 2 + perem[__x], perem[__h2 + j] * k[0] + perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
	//k[2] = f(x + h, (-k + 2 * k)*h + v1);
	k[2] = f(perem[__x] + perem[__h1 + j], (-k[0] + 2 * k[1])*perem[__h1 + j] + perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
	
	if (j)
	{
		double tmp = (k[0] + 4 * k[1] + k[2]) / 6 * perem[__h1 + j] + perem[__v1];

		k[0] = f(perem[__x], perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
		//k[1] = f(h / 2 + x[0], _h[0] *k[0] + v1);
		k[1] = f(perem[__h1 + j] / 2 + perem[__x], perem[__h2 + j] * k[0] + perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
		//k[2] = f(x + h, (-k + 2 * k)*h + v1);
		k[2] = f(perem[__x] + perem[__h1 + j], (-k[0] + 2 * k[1])*perem[__h1 + j] + perem[__v1], start_p[__a1], start_p[__a3], start_p[__m]);
	}

	//return (k[0] + 4 * k[1] + k[2]) / 6 *(*h) + (*v1);
	return (k[0] + 4 * k[1] + k[2]) / 6 * perem[__h1 + j] + perem[__v1];
}

// �������� ������� ������ 9 � ����� perem[__x] ��� ��������� �������� u(x0)=u0
// �� ������ ������ �� ������������
double st_true_sol_ex_9(double *perem, double* start_p)
{
	return sqrt(start_p[__a1]) / sqrt(( (start_p[__a3] + start_p[__a1] / pow(start_p[__u], 2)) * exp(2* start_p[__a1]* start_p[__m]*(perem[__x]- start_p[__x0]) ))- start_p[__a3]);
}


int m_RK3_1_r(double* start_p, int* gran, char* name_txt, double** py)
{
	double v_temp = 0.0;
	double v2 = 0.0;
	//------------------x---v1---e---h
	double perem[P_SIZE] = {};
	double k[3] = {};
	int z = 0;
	double tmp = 0.0;
	vector<double> d_v;
	double C[2] = {};

	string name = string(name_txt);
	ofstream _f(name);


	//������������� �������
	perem[__x] = start_p[__x0];
	perem[__v1] = start_p[__v0];
	perem[__s] = 0.0;
	perem[__h1] = start_p[__h0];
	perem[__h2] = 0.0;
	perem[__h3] = 0.0;
	perem[__u] = start_p[__v0];
	perem[__E] = 0.0;
	perem[__c1] = 0.0;
	perem[__c2] = 0.0;

	//���������� � ������ 1-� ��������
	d_v.push_back(perem[__x]);
	d_v.push_back(perem[__v1]);
	d_v.push_back(perem[__s]);
	d_v.push_back(perem[__h1]);
	d_v.push_back(perem[__u]);
	d_v.push_back(perem[__E]);
	d_v.push_back(perem[__c1]);
	d_v.push_back(perem[__c2]);


	for (int i = 0; perem[gran[_x_u]] < start_p[__gran] && i<static_cast<int>(start_p[__max_step]); i++)
	{
		//���������� 
		v_temp = st_RK_1(perem,start_p, k, 0);
		v2 = st_RK_1(perem,start_p, k, 1);

		perem[__s] = fabs((perem[__v1] - v2) / (pow(2, P) - 1) * pow(2, P));

		if (gran[__contr_e]) //c ���������� ���� ��� ���
		{
			//�������, ���� ��� ������� ����� �� ���� ���������
			if (perem[__s] > EPS)
			{
				i--;
				perem[__h1] = perem[__h1] / 2;
				perem[__c1] += 1.0;
				continue;
			}

			if (perem[__s] < EPS / pow(2, P + 1))
			{
				perem[__h1] = perem[__h1] * 2;
				perem[__c2] += 1.0;

			}
		}

		perem[__u] = st_true_sol_ex_9(perem, start_p);
		perem[__E] = fabs(perem[__u] - perem[__v1]);

		//----------------------------------------------------------------------

		//������ �������� � �����������
		perem[__v1] = v_temp;

		//������ � ������ �� ��� �����
		d_v.push_back(perem[__x]);
		d_v.push_back(perem[__v1]);
		d_v.push_back(perem[__s]);
		d_v.push_back(perem[__h1]);
		d_v.push_back(perem[__u]);
		d_v.push_back(perem[__E]);
		d_v.push_back(perem[__c1]);
		d_v.push_back(perem[__c2]);



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
