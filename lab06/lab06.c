#include <stdio.h>
#include <math.h>

#define abs(X) ((X) > 0 ? (X) : -(X))

#define N 5

double licz_r(double *a, double *b, int n, double xj);

int main()
{
    int L, n, it, i;
    int IT_MAX = 30;
    double x0, x1, x2, R0, R1, R2;
    double a[N + 1] = {240, -196, -92, 33, 14, 1};
    double b[N + 1] = {};

    FILE *plik;
    plik = fopen("wynik.dat", "w");

    for (L = 1; L <= N; L++)
    {
        n = N - L + 1;
        x0 = 0.;
        x1 = 0.1;
        R0 = licz_r(a, b, n, x0);
        R1 = licz_r(a, b, n, x1);

        for (it = 1; it <= IT_MAX; it++)
        {
            x2 = x1 - R1 * (x1 - x0) / (R1 - R0);
            R2 = licz_r(a, b, n, x2);
            R0 = R1;
            R1 = R2;
            x0 = x1;
            x1 = x2;
            fprintf(plik, "%d\t%d\t%15g\t%15g\n", L, it, x2, R2);

            if (abs(x1 - x0) < 1.0E-7)
                break;
        }

        fprintf(plik, "\n\n");

        for (i = 0; i <= (n - 1); i++)
            a[i] = b[i];
    }

    fclose(plik);

    return 0;
}

double licz_r(double *a, double *b, int n, double xj)
{
    int k;
    b[n] = 0.;
    for (k = n - 1; k > -1; k--)
    {
        b[k] = a[k + 1] + xj * b[k + 1];
    }
    return (a[0] + xj * b[0]);
}