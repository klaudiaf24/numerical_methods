#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "nrutil.c"
#include "four1.c"

#define frand() ((double)rand()) / (RAND_MAX + 1.0)

double fun(double t, double T);
double wagaGauss(double t, double sigma);
void splot(float *f, float *g1, float *g2, int nk);
double max(float *f, int nk);

int main()
{
    for (int k = 8; k <= 12; k += 2)
    {

        double Nk = pow(2, k) * 1.0;
        double T = 1.0;
        double tmax = T * 3.0;
        double dt = tmax / Nk;
        double sigma = T / 20.0;
        double t0 = 0.0;
        double t = t0;

        float *f = vector(1, 2 * Nk);
        float *fo = vector(1, 2 * Nk);
        float *g1 = vector(1, 2 * Nk);
        float *g2 = vector(1, 2 * Nk);

        //1.
        for (int i = 1; i <= Nk; i++)
        {

            f[2 * i - 1] = fun(t, T) + (frand() - 0.5); //funkcja zaburzona
            fo[2 * i - 1] = fun(t, T);                  //funkcja niezaburzona
            g1[2 * i - 1] = wagaGauss(t, sigma);
            g2[2 * i - 1] = wagaGauss(t, sigma);
            f[2 * i] = 0.0;
            fo[2 * i] = 0.0;
            g1[2 * i] = 0.0;
            g2[2 * i] = 0.0;
            t += dt;
        }

        //2.
        four1(f, Nk, 1);
        four1(g1, Nk, 1);
        four1(g2, Nk, -1);

        //3.
        splot(f, g1, g2, Nk);

        //4.
        four1(f, Nk, -1);

        //5.
        double f_max;
        f_max = max(f, Nk);

        //6.

        ////////////////////////////////////////
        //k=8
        if (k == 8)
        {
            FILE *plik1;
            plik1 = fopen("wynik8.dat", "w");
            t = 0.0;

            for (int i = 1; i <= Nk; i++)
            {
                fprintf(plik1, "%15g %15g %15g \n", t, fo[2 * i - 1], f[2 * i - 1] * 2.5 / f_max);
                t += dt;
            }
            fclose(plik1);
        }

        ///////////////////////////////////
        //k=10
        if (k == 10)
        {
            FILE *plik2;
            plik2 = fopen("wynik10.dat", "w");
            t = 0.0;

            for (int i = 1; i <= Nk; i++)
            {
                fprintf(plik2, "%15g %15g %15g \n", t, fo[2 * i - 1], f[2 * i - 1] * 2.5 / f_max);
                t += dt;
            }
            fclose(plik2);
        }

        ///////////////////////////////////
        //k=12
        if (k == 12)
        {
            FILE *plik3;
            plik3 = fopen("wynik12.dat", "w");
            t = 0.0;

            for (int i = 1; i <= Nk; i++)
            {
                fprintf(plik3, "%15g %15g %15g \n", t, fo[2 * i - 1], f[2 * i - 1] * 2.5 / f_max);
                t += dt;
            }
            fclose(plik3);
        }
    } //koniec petli zewnetrznej

    return 0;
}

double fun(double t, double T)
{
    double wyn;
    double omega = 2 * M_PI / T;
    wyn = sin(omega * t) + sin(2 * omega * t) + sin(3 * omega * t);
    // wyn += (frand() - 0.5);
    return wyn;
}

double wagaGauss(double t, double sigma)
{
    double wyn;
    wyn = 1 / (sigma * sqrt(2 * M_PI)) * exp((-pow(t, 2)) / (2 * pow(sigma, 2)));
    return wyn;
}

void splot(float *f, float *g1, float *g2, int nk)
{
    float *g = vector(1, 2 * nk);
    float *temp = vector(1, 2 * nk);

    for (int i = 1; i <= nk * 2; i++)
    {
        g[i] = g1[i] + g2[i];
        temp[i] = f[i]; //pomocnicza tablica przechowujaca f
    }

    for (int i = 1; i <= nk; i++)
    {
        f[2 * i - 1] = temp[2 * i - 1] * g[2 * i - 1] - temp[2 * i] * g[2 * i];
        f[2 * i] = temp[2 * i - 1] * g[2 * i] + g[2 * i - 1] * temp[2 * i];
    }

    free_vector(g, 1, 2 * nk);
    free_vector(temp, 1, 2 * nk);
}

double max(float *f, int nk)
{
    double f_max;
    f_max = fabs(f[1]);
    for (int i = 1; i <= nk; i++)
        if (f_max < fabs(f[2 * i - 1]))
            f_max = fabs(f[2 * i - 1]);
    return f_max;
}