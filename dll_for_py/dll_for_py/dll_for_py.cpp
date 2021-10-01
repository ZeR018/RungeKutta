// dll_for_py.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


// test.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include"m_RK3_1.h"

using namespace std;


extern "C" __declspec(dllexport) void __stdcall work_RK31R(double** data, double * d, double * gran, int* _i,int stat_h)
{

	*_i = m_RK3_1_r(d, gran[0], gran[1], gran[2], "test1.txt", data,stat_h);

}

extern "C" __declspec(dllexport) void __stdcall del_mem(double** data)
{
	delete[](*data);
	//cout << "- mem" << endl;
}