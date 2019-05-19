#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Wn(double *x, double **y, const int n, const double x_val);

int main()
{
    int n, i, l, j;
    double m;
    int xmax = 5;
    int xmin = -5;
    double x_step = 0.1;
    double step;

    FILE *Newton1;
    FILE *Newton2;
    FILE *Newton3;
    FILE *Newton4;
    FILE *Ch1;
    FILE *Ch2;
    FILE *Ch3;
    FILE *Ch4;

    //////////////////////////////////////////////////////////////////
    //n=5;
    Newton1 = fopen("Newton1.dat", "w");
    Ch1 = fopen("Ch1.dat", "w");
    n = 5;
    double *x_a = malloc((n + 1) * sizeof(double));
    double **y_a = malloc((n + 1) * sizeof(double *));
    for (i = 0; i < n + 1; i++)
        y_a[i] = malloc((n + 1) * sizeof(double));

    step = (double)(xmax - xmin) / n;
    //Newton
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny Newton
    {
        x_a[l] = xmin + l * step;
        y_a[l][0] = 1.0 / (1.0 + x_a[l] * x_a[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_a[i][j] = (y_a[i][j - 1] - y_a[i - 1][j - 1]) / (x_a[i] - x_a[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Newton1, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_a, y_a, n, x));
    }
    //////////////////////
    //Chebyszew
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny i otptymalizacja polozen wezlow
    {
        x_a[l] = ((xmin - xmax) * cos(M_PI * (2.0 * l + 1.0) / (2.0 * n + 2.0)) + (xmin + xmax)) / 2.0;
        y_a[l][0] = 1.0 / (1.0 + x_a[l] * x_a[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_a[i][j] = (y_a[i][j - 1] - y_a[i - 1][j - 1]) / (x_a[i] - x_a[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Ch1, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_a, y_a, n, x));
    }

    ////////////////////////////////////////////////////////////////
    //n=10
    Newton2 = fopen("Newton2.dat", "w");
    Ch2 = fopen("Ch2.dat", "w");

    n = 10;
    double *x_b = malloc((n + 1) * sizeof(double));
    double **y_b = malloc((n + 1) * sizeof(double *));
    for (i = 0; i < n + 1; i++)
        y_b[i] = malloc((n + 1) * sizeof(double));

    step = (double)(xmax - xmin) / n;
    //Newton
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny Newton
    {
        x_b[l] = xmin + l * step;
        y_b[l][0] = 1.0 / (1.0 + x_b[l] * x_b[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_b[i][j] = (y_b[i][j - 1] - y_b[i - 1][j - 1]) / (x_b[i] - x_b[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Newton2, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_b, y_b, n, x));
    }
    //////////////////////
    //Chebyszew
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny i otptymalizacja polozen wezlow
    {
        x_b[l] = ((xmin - xmax) * cos(M_PI * (2.0 * l + 1.0) / (2.0 * n + 2.0)) + (xmin + xmax)) / 2.0;
        y_b[l][0] = 1.0 / (1.0 + x_b[l] * x_b[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_b[i][j] = (y_b[i][j - 1] - y_b[i - 1][j - 1]) / (x_b[i] - x_b[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Ch2, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_b, y_b, n, x));
    }

    ///////////////////////////////////////////////////////////
    //n=15
    Newton3 = fopen("Newton3.dat", "w");
    Ch3 = fopen("Ch3.dat", "w");

    n = 15;
    double *x_c = malloc((n + 1) * sizeof(double));
    double **y_c = malloc((n + 1) * sizeof(double *));
    for (i = 0; i < n + 1; i++)
        y_c[i] = malloc((n + 1) * sizeof(double));

    step = (double)(xmax - xmin) / n;
    //Newton
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny Newton
    {
        x_c[l] = xmin + l * step;
        y_c[l][0] = 1.0 / (1.0 + x_c[l] * x_c[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_c[i][j] = (y_c[i][j - 1] - y_c[i - 1][j - 1]) / (x_c[i] - x_c[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Newton3, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_c, y_c, n, x));
    }
    //////////////////////
    //Chebyszew
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny i otptymalizacja polozen wezlow
    {
        x_c[l] = ((xmin - xmax) * cos(M_PI * (2.0 * l + 1.0) / (2.0 * n + 2.0)) + (xmin + xmax)) / 2.0;
        y_c[l][0] = 1.0 / (1.0 + x_c[l] * x_c[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_c[i][j] = (y_c[i][j - 1] - y_c[i - 1][j - 1]) / (x_c[i] - x_c[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Ch3, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_c, y_c, n, x));
    }

    ////////////////////////////////////////////////////////////
    //n=20
    Newton4 = fopen("Newton4.dat", "w");
    Ch4 = fopen("Ch4.dat", "w");

    n = 20;
    double *x_d = malloc((n + 1) * sizeof(double));
    double **y_d = malloc((n + 1) * sizeof(double *));
    for (i = 0; i < n + 1; i++)
        y_d[i] = malloc((n + 1) * sizeof(double));

    step = (double)(xmax - xmin) / n;
    //Newton
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny Newton
    {
        x_d[l] = xmin + l * step;
        y_d[l][0] = 1.0 / (1.0 + x_d[l] * x_d[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_d[i][j] = (y_d[i][j - 1] - y_d[i - 1][j - 1]) / (x_d[i] - x_d[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Newton4, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_d, y_d, n, x));
    }
    //////////////////////
    //Chebyszew
    for (l = 0; l < n + 1; l++) //ustawienie 1 kolumny i otptymalizacja polozen wezlow
    {
        x_d[l] = ((xmin - xmax) * cos(M_PI * (2.0 * l + 1.0) / (2.0 * n + 2.0)) + (xmin + xmax)) / 2.0;
        y_d[l][0] = 1.0 / (1.0 + x_d[l] * x_d[l]);
    }

    for (j = 1; j <= n; j++) //wyznczanie niezerowych polozen tabeli
        for (int i = j; i <= n; i++)
            y_d[i][j] = (y_d[i][j - 1] - y_d[i - 1][j - 1]) / (x_d[i] - x_d[i - j]);

    for (m = xmin; m <= xmax; m += x_step)
    {
        double x = m;
        fprintf(Ch4, "%15g\t%15g\t%15g\n", x, 1 / (1 + x * x), Wn(x_d, y_d, n, x));
    }

    fclose(Newton1);
    fclose(Newton2);
    fclose(Newton3);
    fclose(Newton4);
    fclose(Ch1);
    fclose(Ch2);
    fclose(Ch3);
    fclose(Ch4);

    // //Zwalnianie pamieci
    // free(x_a);
    // free(x_b);
    // free(x_c);
    // free(x_d);

    // for (int i = 0; i <= n; i++)
    // {
    //     free(y_a[i]);
    //     free(y_b[i]);
    //     free(y_c[i]);
    //     free(y_d[i]);
    // }
    // free(y_a);
    // free(y_b);
    // free(y_c);
    // free(y_d);

    return 0;
}

double Wn(double *x, double **y, const int n, const double x_val)
{
    double wn = 0.0;
    for (int j = 0; j <= n; j++)
    {
        double iloczyn = 1.0;
        for (int i = 0; i < j; i++)
        {
            iloczyn *= (x_val - x[i]);
        }
        wn += y[j][j] * iloczyn;
    }

    return wn;
}
