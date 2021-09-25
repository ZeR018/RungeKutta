// dll_for_py.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


// test.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include"m_RK3_1.h"

using namespace std;


extern "C" __declspec(dllexport) void __stdcall work_RK31R(double** data, double * d, double * max, int* _i)
{

	*_i = m_RK3_1_r(d[0], d[1], d[2], max[0], max[1], "test1.txt", data);
	//return m_RK3_1_r(d[0], d[1], d[2], max[0], max[1], "test1.txt", data);
}

