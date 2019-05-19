#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "gaussj.c"

#define frand() ((double)rand()) / (RAND_MAX + 1.0)

double fun(double x, int xmax, int xmin, double x0);
double f(double x, int xmax, int xmin, double x0); //fun bez szumu
double sum1(double *x, double **phi, int N, int j);
double sum2(double *x, double **phi, int N, int j);
double sum3(double **phi, int N, int j);

int main()
{
    int xmax = 4;
    int xmin = -4;
    int N = 201;
    double deltax = (xmax - xmin) / (N - 1.0);
    double phi0 = 1.0;
    double beta = 0.0;
    double alfa = 0.0;
    double x0 = 2.0;
    double *x = dvector(0, N - 1);
    double *y = dvector(0, N - 1);
    double *y_n = dvector(0, N - 1);
    int m = 50;

    double **phi = (double **)malloc((m + 1) * sizeof(double *)); //wiersz - konkretny wielomian, kolumna - wartosc w punktach
    for (int i = 0; i < (m + 1); i++)
        phi[i] = (double *)malloc(N * sizeof(double));

    //uzupelnienie x i y
    double xx = xmin;

    for (int i = 0; i < N; i++)
    {
        x[i] = xx;
        y[i] = fun(xx, xmax, xmin, x0);
        y_n[i] = f(xx, xmax, xmin, x0); //bez szumu
        xx += deltax;
    }

    //1.
    //phi0
    for (int i = 0; i < N; i++)
    {
        phi[0][i] = phi0;
    }

    //phi1 - beta = 0
    alfa = sum1(x, phi, N, 0) / sum3(phi, N, 0);
    for (int i = 0; i < N; i++)
    {
        phi[1][i] = (x[i] - alfa) * phi[0][i];
    }

    //phi....
    for (int j = 2; j < (m + 1); j++)
    {
        alfa = sum1(x, phi, N, j - 1) / sum3(phi, N, j - 1);
        beta = sum2(x, phi, N, j - 1) / sum3(phi, N, j - 2);

        for (int i = 0; i < N; i++)
        {
            phi[j][i] = (x[i] - alfa) * phi[j - 1][i] - beta * phi[j - 2][i];
        }
    }

    //3.
    FILE *plik;
    plik = fopen("wynik.dat", "w");
    for (int i = 0; i < N; i++)
    {
        fprintf(plik, "%10g", x[i]);
        for (int j = 0; j < 7; j++)
            fprintf(plik, "\t%g", phi[j][i] / phi[j][0]);

        fprintf(plik, "\n");
    }

    //4.

    // m = 10
    m = 10;

    FILE *plik1;
    plik1 = fopen("wynik10.dat", "w");
    for (int k = 0; k < N; k++)
    {
        double F = 0;
        for (int j = 0; j <= m; j++)
        {
            double c = 0;
            double s = 0;
            for (int i = 0; i < N; i++)
            {
                c += y[i] * phi[j][i];
                s += phi[j][i] * phi[j][i];
            }
            F += (c / s) * phi[j][k];
        }
        fprintf(plik1, "%15f %15f %15f %15f\n", x[k], y_n[k], y[k], F);
    }
    // m = 30;

    m = 30;

    FILE *plik2;
    plik2 = fopen("wynik30.dat", "w");
    for (int k = 0; k < N; k++)
    {
        double F = 0;
        for (int j = 0; j <= m; j++)
        {
            double c = 0;
            double s = 0;
            for (int i = 0; i < N; i++)
            {
                c += y[i] * phi[j][i];
                s += phi[j][i] * phi[j][i];
            }
            F += (c / s) * phi[j][k];
        }
        fprintf(plik2, "%15f %15f %15f %15f\n", x[k], y_n[k], y[k], F);
    }

    // m = 50;
    m = 50;

    FILE *plik3;
    plik3 = fopen("wynik50.dat", "w");
    for (int k = 0; k < N; k++)
    {
        double F = 0;
        for (int j = 0; j <= m; j++)
        {
            double c = 0;
            double s = 0;
            for (int i = 0; i < N; i++)
            {
                c += y[i] * phi[j][i];
                s += phi[j][i] * phi[j][i];
            }
            F += (c / s) * phi[j][k];
        }
        fprintf(plik3, "%15f %15f %15f %15f\n", x[k], y_n[k], y[k], F);
    }

    fclose(plik);
    fclose(plik1);
    fclose(plik2);
    fclose(plik3);

    return 0;
}

double fun(double x, int xmax, int xmin, double x0)
{
    double wyn;
    double sigma = (xmax - xmin) / 16.0;
    wyn = sin((14 * M_PI * x) / (xmax - xmin)) *
          (exp(-pow(x - x0, 2) / (2 * pow(sigma, 2))) +
           exp(-pow(x + x0, 2) / (2 * pow(sigma, 2))));
    wyn += (frand() - 0.5) / 5;
    return wyn;
}

double f(double x, int xmax, int xmin, double x0)
{
    double wyn;
    double sigma = (xmax - xmin) / 16.0;
    wyn = sin((14 * M_PI * x) / (xmax - xmin)) *
          (exp(-pow(x - x0, 2) / (2 * pow(sigma, 2))) +
           exp(-pow(x + x0, 2) / (2 * pow(sigma, 2))));
    // wyn += (frand() - 0.5) / 5;
    return wyn;
}

double sum1(double *x, double **phi, int N, int j) //licznik alfa
{
    double wyn = 0.0;
    for (int i = 0; i < N; i++)
        wyn += x[i] * pow(phi[j][i], 2);
    return wyn;
}
double sum2(double *x, double **phi, int N, int j) //liczbik beta
{
    double wyn = 0.0;
    for (int i = 0; i < N; i++)
        wyn += x[i] * phi[j - 1][i] * phi[j][i];
    return wyn;
}

double sum3(double **phi, int N, int j) //mianownik
{
    double wyn = 0.0;
    for (int i = 0; i < N; i++)
        wyn += pow(phi[j][i], 2);
    return wyn;
}