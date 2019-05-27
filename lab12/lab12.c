#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "nrutil.c"

double fun1(double x);
double fun2(double x);
double fun3(double x);
void setFirstColumn(double **D, int n, int a, int b, double (*fun)(double));
void setAllMatrix(double **D, int n, int a, int b);
double sum(int w, double h, int a, double (*fun)(double));
void save(double **D, int n, FILE *plik);

int main()
{
    int n;
    int a, b;

    ////////////////////////
    //1.
    ////////////////////////
    FILE *zad1;
    n = 7;
    a = 0;
    b = 1;
    double **D = dmatrix(0, n, 0, n);

    D[0][0] = ((fun1(a) + fun1(b)) * (b - a)) / 2.0;

    setFirstColumn(D, n, a, b, fun1);

    setAllMatrix(D, n, a, b);

    zad1 = fopen("zad1.dat", "w");
    save(D, n, zad1);

    fclose(zad1);
    free_dmatrix(D, 0, n, 0, n);

    ////////////////////////
    //2.
    ////////////////////////
    FILE *zad2;
    n = 15;
    a = -1;
    b = 1;
    D = dmatrix(0, n, 0, n);

    D[0][0] = ((fun2(a) + fun2(b)) * (b - a)) / 2.0;

    setFirstColumn(D, n, a, b, fun2);

    setAllMatrix(D, n, a, b);

    zad2 = fopen("zad2.dat", "w");
    save(D, n, zad2);

    fclose(zad2);
    free_dmatrix(D, 0, n, 0, n);

    ////////////////////////
    //3.
    ////////////////////////
    FILE *zad3;
    n = 7;
    a = 0; //zmiana granic po podstawnieniu
    b = 1;
    D = dmatrix(0, n, 0, n);

    D[0][0] = ((fun3(a) + fun3(b)) * (b - a)) / 2.0;

    setFirstColumn(D, n, a, b, fun3);

    setAllMatrix(D, n, a, b);

    zad3 = fopen("zad3.dat", "w");
    save(D, n, zad3);

    fclose(zad3);
    free_dmatrix(D, 0, n, 0, n);

    return 0;
}

double fun1(double x)
{
    double y;

    double epsilon = pow(10, -7);
    if (fabs(x) < epsilon)
        x += epsilon;

    y = 1.0 * sin(x) / x;
    return y;
}

double fun2(double x)
{
    double y;

    double epsilon = pow(10, -7);
    if (fabs(x) < epsilon)
        x += epsilon;

    y = (1.0 * cos(x) - exp(x)) / sin(x);
    return y;
}

double fun3(double t) //po podstawnieniu
{
    double y;

    double epsilon = pow(10, -7);
    if (fabs(t) < epsilon)
        t += epsilon;

    y = (1.0 / t) * exp(-1.0 / t);
    return y;
}

void setFirstColumn(double **D, int n, int a, int b, double (*fun)(double))
{
    double h;
    for (int w = 1; w < n + 1; w++)
    {
        h = (b - a) / pow(2, w);
        D[w][0] = D[w - 1][0] / 2.0 + h * sum(w, h, a, fun);
    }
}

double sum(int w, double h, int a, double (*fun)(double))
{
    double wyn = 0.0;
    for (int i = 1; i <= pow(2, w - 1); i++)
        wyn += fun(a + (2 * i - 1) * h);
    return wyn;
}

void setAllMatrix(double **D, int n, int a, int b)
{
    for (int k = 1; k < n + 1; k++)
        for (int w = k; w < n + 1; w++)
            D[w][k] = (pow(4, k) * D[w][k - 1] - D[w - 1][k - 1]) / (pow(4, k) - 1.0);
}

void save(double **D, int n, FILE *plik)
{
    for (int w = 0; w < n + 1; w++)
        fprintf(plik, "%d \t %20g \t %20g\n", w, D[w][0], D[w][w]);
}