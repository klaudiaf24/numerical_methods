#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "nrutil.c"
#include "bessi0.c"
#include "gauher.c"

double lengthVec(double *a, double *b);

int main()
{
    FILE *plik1;
    plik1 = fopen("wyn5.dat", "a+");
    FILE *plik2;
    plik2 = fopen("wyn10.dat", "a+");
    FILE *plik3;
    plik3 = fopen("wyn15.dat", "a+");
    FILE *plik4;
    plik4 = fopen("wyn20.dat", "a+");
    FILE *plik5;
    plik5 = fopen("wyn25.dat", "a+");
    FILE *plik6;
    plik6 = fopen("wyn30.dat", "a+");
    FILE *plik7;
    plik7 = fopen("wyn35.dat", "a+");

    for (int n = 5; n <= 35; n += 5)
    {
        for (double x20 = 0.1; x20 <= 6.0; x20 += 0.1)
        {
            float *x1 = vector(1, n);
            float *w1 = vector(1, n);
            float *x2 = vector(1, n + 1);
            float *w2 = vector(1, n + 1);
            double sigma = 1.0 / sqrt(2);

            double *R10 = dvector(1, 2);
            R10[1] = 0.0;
            R10[2] = 0.0;

            double *R20 = dvector(1, 2);
            R20[1] = x20;
            R20[2] = 0.0;

            double r0 = fabs(lengthVec(R10, R20));

            //////
            //1.
            /////

            double Vdok = 0.0;
            Vdok = pow((2 * M_PI), 2) 
                    * pow(sigma, 4) 
                    * (sqrt(M_PI) / (2 * sigma)) 
                    * exp(-pow(r0, 2) 
                    / (8 * pow(sigma, 2))) 
                    * bessi0(pow(r0, 2) / (8 * pow(sigma, 2)));

            //////
            //2.
            //////

            gauher(x1, w1, n);
            gauher(x2, w2, n + 1);

            //////
            //3.
            //////

            double Vnum = 0.0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n + 1; j++)
                    for (int k = 1; k <= n; k++)
                        for (int l = 1; l <= n + 1; l++)
                            Vnum += (w1[i] * w2[j] * w1[k] * w2[l]) /
                                    (sqrt(pow(x1[i] - x2[j] + x20, 2) + pow(x1[k] - x2[l], 2)));

            //////
            //4.
            //////

            double epsilon;
            epsilon = fabs((Vdok - Vnum) / Vdok);

            //////
            //ZAPIS DO PLIKU
            //////

            if (n == 5)
                fprintf(plik1, "%10g %20g\n", x20, epsilon);

            else if (n == 10)
                fprintf(plik2, "%10g %20g\n", x20, epsilon);

            else if (n == 15)
                fprintf(plik3, "%10g %20g\n", x20, epsilon);

            else if (n == 20)
                fprintf(plik4, "%10g %20g\n", x20, epsilon);

            else if (n == 25)
                fprintf(plik5, "%10g %20g\n", x20, epsilon);

            else if (n == 30)
                fprintf(plik6, "%10g %20g\n", x20, epsilon);

            else if (n == 35)
                fprintf(plik7, "%10g %20g\n", x20, epsilon);

            free_vector(x1, 1, n);
            free_vector(w1, 1, n);
            free_vector(x2, 1, n + 1);
            free_vector(w2, 1, n + 1);
            free_dvector(R10, 1, 2);
            free_dvector(R20, 1, 2);
        }
    }

    fclose(plik1);
    fclose(plik2);
    fclose(plik3);
    fclose(plik4);
    fclose(plik5);
    fclose(plik6);
    fclose(plik7);
}

double lengthVec(double *a, double *b)
{
    double wyn;
    wyn = sqrt(pow(b[1] - a[1], 2) + pow(b[2] - a[2], 2));
    return wyn;
}
