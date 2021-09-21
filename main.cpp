#include <iostream>
#include <math.h>

// m, a1, a3 > 0
double m;
double a1, a3;

// 9 задача вариант 4
// m du/dx = R
// R = -(a1*u + a3*u^3)
double func (double u) {
    return -(a1 * u + a3 * u * u * u) / m;
}

double* rungeCuttaMethod (double (*func)(double), double h, double x0,  double maxX) {
    double k1, k2, k3, k4;

    int n = maxX/h;
    double *res = new double [n];
    double x = x0;
    int i = 1;
    res[0] = x0;

    for(double t = 0; t < maxX-h; t+=h) {

        k1 = func(x);
        k2 = func(x + k1 * h / 2.0);
        k3 = func(x + k2 * h/ 2.0);
        k4 = func(x + k3 * h/ 2.0);

        x+=(h/6.0)*(k1+2*k2+2*k3+k4);
        res[i] = x;
        i++;
    }

    return res;
};

int main() {
    a1 = 1;
    a3 = 1;
    m = 1;

    double h = 0.01; // Шаг h
    double x0 = 1;
    double maxX = 5;
    double * RKres = new double [maxX/h];
    RKres = rungeCuttaMethod(func, h, x0, maxX);


    for(int i = 0; i < maxX/h; i++) {
        std::cout << i;
        std::cout << " ";
        std::cout << RKres[i]<< std::endl;
    }
};