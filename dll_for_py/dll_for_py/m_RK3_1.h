#pragma once
#include <string.h>
#include<iostream>
#include <vector>
#include <cstring>
#include<string>
#include <math.h>

using namespace std;




double st_RK_1(double* perem, double *k, int j);
int m_RK3_1_r(double x, double v1, double h, double max_x, double max_v, char* name_txt, double** py);