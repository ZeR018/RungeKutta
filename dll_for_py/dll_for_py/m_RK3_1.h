#pragma once
#include <string.h>
#include<iostream>
#include <vector>
#include <cstring>
#include<string>
#include <math.h>

using namespace std;




double st_RK_1(double* perem, double* start_p, double *k, int j);

int m_RK3_1_r(double* start_p,double min_v, double max_x, double max_v, char* name_txt, double** py);