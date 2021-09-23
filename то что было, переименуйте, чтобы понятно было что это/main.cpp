#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
#define FILE_NAME "D:\\1Study\\C++\\RungeKutta\\RK4results.txt"

// m, a1, a3 > 0
double m;
double a1, a3;

// 9 задача вариант 4
// m du/dx = R
// R = -(a1*u + a3*u^3)
double func9 (double u) {
    return -(a1 * u + a3 * u * u * u) / m;
}

double* rungeCuttaMethod (double (*func)(double), double h, double u0,  double maxX) {
    double k1, k2, k3, k4;

    int n = maxX/h;
    double *res = new double [n];
    double u = u0;
    int i = 1;
    res[0] = u0;

    for(double x = 0; x < maxX-h; x+=h) {

        k1 = func(u);
        k2 = func(u + k1 * h / 2.0);
        k3 = func(u + k2 * h/ 2.0);
        k4 = func(u + k3 * h/ 2.0);

        u+=(h/6.0)*(k1+2*k2+2*k3+k4);
        res[i] = u;
        i++;
    }

    return res;
};

double* exactSol9 (double h, double u0,  double maxX) {
    int n = maxX/h;
    double *res = new double [n];
    int i = 1;
    res[0] = u0;
    double c = (a1 / (u0 * u0)) + a3;

    return res;
}

void clean(const char *fName) {
ofstream fout;
fout.open(fName, ios::trunc);
fout.close();
}

int main() {
    a1 = 2;
    a3 = 5;
    m = 1;

    double h = 0.01; // Шаг h
    double u0 = 1;
    double maxX = 5;
    double * RKres = new double [maxX/h];
    RKres = rungeCuttaMethod(func9, h, u0, maxX);
    double * exactRes = new double [maxX/h];
    exactRes = exactSol9(h, u0, maxX);


//    for(int i = 0; i < maxX/h; i++) {
//        cout << i;
//        cout << " ";
//        cout << RKres[i]<< endl;
//    }

    clean(FILE_NAME);
    ofstream fout;
    fout.open(FILE_NAME, ios::app);
    fout << "a1:" << a1 << ", a3:" << a3 << ", m: " << m << ", u0: " << u0 << endl << endl;
    fout << "i" << ": " << "RK, " << "Exact, " << "inaccuracy" << endl;
    for(int i = 0; i < maxX/h; i++) {
        fout << i << ": " << RKres[i] << ", " << exactRes[i] << ", " << (exactRes[i] - RKres[i]) << endl;
    }

};