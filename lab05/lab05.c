#include <math.h>
#include <stdio.h>
#include <time.h>

#include "nrutil.h"
#include "nrutil.c"

#define abs(X) ((X) > 0 ? (X) : -(X))

#define N 7

double Mskalarne(double *A, double *B, int n);
double norma(double *r, int n);
void mnozMacierzVektor(int n, double **A, double *x, double *wynik);
void przypiszMacierzWynikowa(double **A, double *vec, int k, int size);
void orto(double *vecWyn, double **A, int kolumna, int size);
void przypiszWektor(double *vec, double *vecWyn, int size);
void MacierzMacierz(double **Wynik, double **X, double **A, int size);

int main()
{
    int i, j, k;
    double **A;
    double **D;
    double **WynikX;
    int K_val = N;
    int IT_MAX = 12;
    double *x;
    double *temp;
    double lambda;

    FILE *plik1;
    FILE *plik2;
    FILE *plik3;

    A = dmatrix(0, N - 1, 0, N - 1);
    D = dmatrix(0, N - 1, 0, N - 1);
    WynikX = dmatrix(0, N - 1, 0, N - 1);
    temp = dvector(0, N - 1);
    x = dvector(0, N - 1);

    // 1.
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = 1. / sqrt(2 + abs(i - j));

    //2.

    plik1 = fopen("przyblizeniaLambda.dat", "w");

    double **MacierzLambd; //do łatwiejszego zapisu do pliku
    MacierzLambd = dmatrix(0, IT_MAX - 1, 0, N - 1);

    for (k = 0; k < K_val; k++)
    {
        for (i = 0; i < N; i++) //inicjalizacja wektora startowego
            x[i] = 1.;

        for (i = 1; i <= IT_MAX; i++)
        {
            mnozMacierzVektor(N, A, x, temp);
            for (j = 0; j < k; j++)
            {
                orto(temp, WynikX, j, N);
            }
            lambda = Mskalarne(temp, x, N) / Mskalarne(x, x, N);
            MacierzLambd[i - 1][k] = lambda;
            przypiszWektor(temp, x, N);
        }

        //fprintf(plik1, "\n");
        przypiszMacierzWynikowa(WynikX, x, k, N);
    }
    //MACIERZ LAMBD

    for (i = 0; i < IT_MAX; i++)
    {
        fprintf(plik1, "%d\t", i + 1);
        for (j = 0; j < N; j++)
            fprintf(plik1, "%15g", MacierzLambd[i][j]);
        fprintf(plik1, "\n");
    }

    /////////////

    plik2 = fopen("MacierzWynik.dat", "w");

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            fprintf(plik2, "%15g", WynikX[i][j]);
        fprintf(plik2, "\n");
    }

    // 3.

    plik3 = fopen("MacierzD.dat", "w");
    double **Temp1;
    double **Temp2;
    Temp1 = dmatrix(0, N - 1, 0, N - 1);
    Temp2 = dmatrix(0, N - 1, 0, N - 1);

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            Temp1[i][j] = WynikX[j][i];
            Temp2[i][j] = WynikX[j][i];
        }

    MacierzMacierz(Temp1, Temp2, A, N); //Temp1 wynik
    MacierzMacierz(D, Temp1, WynikX, N);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            fprintf(plik3, "%15g", D[i][j]);
        }
        fprintf(plik3, "\n");
    }

    fclose(plik1);
    fclose(plik2);
    fclose(plik3);

    // matrix_free(A, 0, N - 1, 0, N - 1);
    // matrix_free(D, 0, N - 1, 0, N - 1);
    // matrix_free(WynikX, 0, N - 1, 0, N - 1);
    // vector_free(temp, 0, N - 1);
    // vector_free(x, 0, N - 1);
    // matrix_free(MacierzLambd, 0, IT_MAX - 1, 0, N - 1);

    // matrix_free(Temp1, 0, N - 1, 0, N - 1);
    // matrix_free(Temp2, 0, N - 1, 0, N - 1);

    return 0;
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

void mnozMacierzVektor(int n, double **A, double *x, double *wynik)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        wynik[i] = 0.0;
        for (j = 0; j < n; j++)
            wynik[i] += A[i][j] * x[j];
    }
}

void przypiszMacierzWynikowa(double **A, double *vec, int k, int size)
{
    int i;
    for (i = 0; i < size; i++)
        A[i][k] = vec[i];
}

void orto(double *vecWyn, double **A, int kolumna, int size)
{
    int i, j;
    double temp = 0.;

    for (i = 0; i < size; i++)
    {
        temp += vecWyn[i] * A[i][kolumna];
    };

    for (i = 0; i < size; i++)
    {
        vecWyn[i] = vecWyn[i] - temp * A[i][kolumna];
    };
}

void przypiszWektor(double *vec, double *vecWyn, int size)
{
    int i;
    for (i = 0; i < size; i++)
        vecWyn[i] = vec[i] / norma(vec, size);
}

void MacierzMacierz(double **Wynik, double **X, double **A, int size)
{
    int i, j, k;
    double Temp;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            Temp = 0.;
            for (k = 0; k < size; k++)
                Temp += X[i][k] * A[k][j];
            Wynik[i][j] = Temp;
        }
    }
}
