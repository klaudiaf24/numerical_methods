#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "nrutil.h"
#include "nrutil.c"

double generator1();
double generator2();
double generator3();

int main()
{
    int N;
    N = 2000;
    //N = pow(10, 4);
    //N = pow(10, 7);
    FILE *gen1;
    FILE *gen2;
    FILE *gen3;

    //1 .
    double *a = (double *)malloc(N * sizeof(double));
    double *b = (double *)malloc(N * sizeof(double));

    gen1 = fopen("generator1.dat", "w");
    gen2 = fopen("generator2.dat", "w");
    gen3 = fopen("generator3.dat", "w");

    for (int i = 0; i < N; i++)
    {
        a[i] = generator1();
        b[i] = generator2();
    }

    for (int i = 0; i <= (N - 4); i++)
    {
        fprintf(gen1, "%10g %10g %10g %10g\n", a[i], a[i + 1], a[i + 2], a[i + 3]);
        fprintf(gen2, "%10g %10g %10g %10g\n", b[i], b[i + 1], b[i + 2], b[i + 3]);
    }

    //2.
    double *c = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++)
        c[i] = generator3();

    for (int i = 0; i <= (N - 4); i++)
        fprintf(gen3, "%10g %10g %10g %10g\n", c[i], c[i + 1], c[i + 2], c[i + 3]);

    //Rozklad jenorodny kuli 3D
    //1.
    double **vec = dmatrix(1, N, 1, 3);
    FILE *sfera;
    sfera = fopen("sfera.dat", "w");

    for (int i = 1; i <= N; i++)
    {
        double u1 = generator3();
        double u2 = generator3();
        double u3 = generator3();
        double u4 = generator3();
        vec[i][1] = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2); //x
        vec[i][2] = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2); //y
        vec[i][3] = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4); //z

        //Normalizacja
        double norma = sqrt(pow(vec[i][1], 2) + pow(vec[i][2], 2) + pow(vec[i][3], 2));
        vec[i][1] /= norma; //x
        vec[i][2] /= norma; //y
        vec[i][3] /= norma; //z
    }

    for (int i = 1; i <= N; i++)
        fprintf(sfera, "%10g %10g %10g\n", vec[i][1], vec[i][2], vec[i][3]);

    //2.
    int d = 3;
    FILE *kula;
    kula = fopen("kula.dat", "w");

    for (int i = 1; i <= N; i++)
    {
        double s = pow(generator3(), (1.0 / d));
        vec[i][1] *= s; //x
        vec[i][2] *= s; //y
        vec[i][3] *= s; //z
    }

    for (int i = 1; i <= N; i++)
        fprintf(kula, "%10g %10g %10g\n", vec[i][1], vec[i][2], vec[i][3]);

    //3.
    int K = 10;
    double delta = 1.0 / K;
    double *n = dvector(1, 10);
    double *g = dvector(1, 10);
    int j;
    FILE *hist;
    hist = fopen("hist.dat", "w");

    //zerowanie n i g
    for (int i = 1; i <= 10; i++)
    {
        n[i] = 0.0;
        g[i] = 0.0;
    }

    for (int i = 1; i <= N; i++)
    {
        double norma = sqrt(pow(vec[i][1], 2) + pow(vec[i][2], 2) + pow(vec[i][3], 2));
        j = (int)(norma / delta) + 1;
        n[j]++;
    }

    double R_nowe, R_stare, V_nowe, V_stare;
    for (int i = 1; i <= N; i++)
    {
        double norma = sqrt(pow(vec[i][1], 2) + pow(vec[i][2], 2) + pow(vec[i][3], 2));
        j = (int)(norma / delta) + 1;
        R_nowe = delta * j;
        R_stare = delta * (j - 1);
        V_nowe = 4.0 / 3.0 * M_PI * pow(R_nowe, 3);
        V_stare = 4.0 / 3.0 * M_PI * pow(R_stare, 3);
        g[j] = n[j] / (V_nowe - V_stare);
    }

    for (int i = 1; i <= K; i++)
    {
        fprintf(hist, "%d %10g %10g\n", i, n[i], g[i]);
    }

    return 0;
}

double generator1()
{
    static long int x = 10;
    int a = 17;
    long int m = pow(2, 13) - 1;
    x = (a * x) % m;
    return x / (m + 1.0);
}

double generator2()
{
    static long int x = 10;
    int a = 85;
    long int m = pow(2, 13) - 1;
    x = (a * x) % m;
    return x / (m + 1.0);
}

double generator3()
{
    static long int x = 10;
    static long int x1 = 10;
    static long int x2 = 10;
    static long int x3 = 10;

    int a = 1176;
    int b = 1476;
    int c = 1776;
    long int m = pow(2, 32) - 5;

    x = (a * x1 + b * x2 + c * x3) % m;
    x3 = x2;
    x2 = x1;
    x1 = x;

    return x / (m + 1.0);
}