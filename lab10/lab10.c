#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "nrutil.c"
#include "gaussj.c"

double fun(double x, double y);
void macierz_odw2(double **A, double **A_odw);
int przyblizenie(double *r, double omega, double **A, double *gradient, double step, double x0, double y0);
double gradx(double x0, double y0, double step);
double grady(double x0, double y0, double step);

int main()
{
    double xmin = -10.0;
    double xmax = 10.0;
    double ymin = -10.0;
    double ymax = 10.0;
    double step = 0.01;
    double wykres_step = 0.1;

    double **A = dmatrix(0, 2, 0, 2);
    A[0][0] = A[1][1] = 2;
    A[0][1] = A[1][0] = 1;

    // 1.
    FILE *wykres_kont;
    wykres_kont = fopen("zad1.dat", "w");
    for (double x = xmin + wykres_step; x < xmax; x += wykres_step)
        for (double y = ymin + wykres_step; y < ymax; y += wykres_step)
            fprintf(wykres_kont, "%10g %10g %10g\n", x, y, fun(x, y));

    // 2.
    double **A_odw = dmatrix(0, 2, 0, 2);
    macierz_odw2(A, A_odw);

    double *b = dvector(0, 2);
    b[0] = b[1] = -4.0;

    double *rmin = dvector(0, 2);
    rmin[0] = rmin[1] = 0.0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            rmin[j] += b[j] * (-A_odw[i][j]);

    printf("%10g %10g\n", rmin[0], rmin[1]);

    //3.
    FILE *zad3;
    double omega = 1.0;
    double *gradient = dvector(0, 2);

    zad3 = fopen("zad3.dat", "w");
    double x0, y0;

    x0 = y0 = 0.0;

    int licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad3, "(%10g,%10g) \t %d \t %10g \t %10g\n", x0, y0, licz, rmin[0], rmin[1]);

    x0 = 10.0;
    y0 = -10.0;

    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad3, "(%10g,%10g) \t %d \t %10g \t %10g\n", x0, y0, licz, rmin[0], rmin[1]);
    x0 = y0 = 100.0;

    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad3, "(%10g,%10g) \t %d \t %10g \t %10g\n", x0, y0, licz, rmin[0], rmin[1]);
    x0 = y0 = 500.0;

    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad3, "(%10g,%10g) \t %d \t %10g \t %10g\n", x0, y0, licz, rmin[0], rmin[1]);

    //4.
    FILE *zad4;
    zad4 = fopen("zad4.dat", "w");

    x0 = y0 = 10.0;

    omega = 0.1;
    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad4, "%g \t %d \t %10g \t %10g\n", omega, licz, rmin[0], rmin[1]);

    omega = 0.4;
    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad4, "%g \t %d \t %10g \t %10g\n", omega, licz, rmin[0], rmin[1]);

    omega = 0.7;
    licz = przyblizenie(rmin, omega, A_odw, gradient, step, x0, y0);
    fprintf(zad4, "%g \t %d \t %10g \t %10g\n", omega, licz, rmin[0], rmin[1]);

    fclose(wykres_kont);
    fclose(zad3);
    fclose(zad4);
    return 0;
}

double fun(double x, double y)
{
    return (x * x - 4 * x + y * y - 4 * y + x * y);
}

void macierz_odw2(double **A, double **A_odw)
{
    double wsp = 1.0 / (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
    A_odw[0][0] = wsp * A[0][0];
    A_odw[1][0] = wsp * (-A[1][0]);
    A_odw[0][1] = wsp * (-A[0][1]);
    A_odw[1][1] = wsp * A[1][1];
}

double Mskalarne(double *A, double *B, int n)
{
    int i;
    double suma = 0.;
    for (i = 0; i < n; i++)
    {
        suma += A[i] * B[i];
    }
    return suma;
}

double norma(double *r, int n)
{
    return sqrt(Mskalarne(r, r, n));
}

void Matrix_Vector(double **A, double *grad, double *temp)
{
    temp[0] = temp[1] = 0.0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            temp[i] += grad[j] * A[i][j];
}

int przyblizenie(double *r, double omega, double **A, double *gradient, double step, double x0, double y0)
{
    int iter = 0;
    double war_zak = pow(10, -6);
    double *rn = dvector(0, 2);
    double *temp = dvector(0, 2);
    double *rrr = dvector(0, 2);
    r[0] = x0;
    r[1] = y0;

    while (1)
    {
        gradient[0] = gradx(r[0], r[1], step);
        gradient[1] = grady(r[0], r[1], step);
        Matrix_Vector(A, gradient, temp);
        rn[0] = r[0] - omega * temp[0];
        rn[1] = r[1] - omega * temp[1];

        rrr[0] = rn[0] - r[0];
        rrr[1] = rn[1] - r[1];

        iter++;
        if (norma(rrr, 2) < war_zak)
            break;

        r[0] = rn[0];
        r[1] = rn[1];
    }

    return iter;
}

double gradx(double x0, double y0, double step)
{
    return ((fun(x0 + step, y0) - fun(x0 - step, y0)) / (2 * step));
}

double grady(double x0, double y0, double step)
{
    return ((fun(x0, y0 + step) - fun(x0, y0 - step)) / (2 * step));
}
