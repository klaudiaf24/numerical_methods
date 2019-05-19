#include <math.h>
#include <stdio.h>
#include <time.h>

#include "nrutil.h"
#include "nrutil.c"
#include "gaussj.c"

#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))

#define N 1000

double Mskalarne(float *A, float *B, int n);
double norma(float *r, int n);
void mnozMacierzVektor(int n, float ** A, float *x, float *wynik, int m);


int main(){
    int i, j;
    float** A;
    float* x;
    float* b;
    int m = 5;

    A = matrix(1, N, 1, N);
    b = vector(1, N);
    x = vector(1, N);

// 1. 2. 3.
    for(i=0 ; i<N ; i++){
        x[i+1] = 0;
        b[i+1] = i+1;
        for(j=0 ; j<N ; j++){
            if( (abs(i-j) ) <= m )
                A[i+1][j+1] = 1.0/( 1+ abs(i-j) );
            else
                A[i+1][j+1] = 0;
        }
    }

// 4.
    float *v;
    float *r;
    float *y;
    double alfa = 0.;
    double beta = 0.;
    int k = 0; //ilosc iteracji
	double  licznik = 0, mianownik = 0;
    float *Temp;
    FILE *plik;

    v = vector(1,N);
    r = vector(1,N);
    y = vector(1,N);
    Temp = vector(1,N);

    time_t czasStart, czasKoniec, t1, t2;
    double czas , czas2; //roznica czasu

    time(&czasStart);

	mnozMacierzVektor(N, A, x, y, m);
	
	for (i = 1; i <= N; i++){
		v[i] = r[i] = b[i] - y[i];
	}
	
	plik = fopen("wynik.dat","w");

	while (norma(r, N) > pow (10, -6)){
        licznik = Mskalarne(r, r, N);
		mnozMacierzVektor(N, A, v, Temp, m);
		mianownik = Mskalarne(v, Temp, N);

		alfa = licznik/mianownik;
		
		for(i = 1; i <= N; i++){
			x[i] = x[i] + alfa*v[i];
			r[i] = r[i] - alfa*Temp[i];
		}

		beta = Mskalarne(r,r,N)/licznik;

		for(i = 1; i <=N; i++){
			v[i] = r[i] + beta*v[i];
		}

// 5.
        fprintf(plik, "%d\t%15g\t%15g\t%15g\t%15g\n", k, norma(r, N), alfa, beta, norma(x, N));
		k++;
    }

    time(&czasKoniec);
    czas = difftime(czasKoniec, czasStart);

    time(&t1);
    float **B;
    B = matrix(1,N,1,1);
    for(i=1; i<=N; ++i){
		B[i][1] = i;
	}

    gaussj(A,N,B,1);
    time(&t2);
    czas2 = difftime(t2,t1);

    printf("\nCzas trwania rozwizania ukladu metoda iteracyjna: %g\n", czas);
    printf("Czas trwania rozwizania ukladu metoda eliminacj zupelnej: %g\n\n", czas2);
    



    fclose(plik);
    free_matrix(A, 1, N, 1, N);
    free_matrix(B, 1, N, 1, N);
    free_vector(b, 1, N);
    free_vector(x, 1, N);
    free_vector(v, 1, N);
    free_vector(r, 1, N);
    free_vector(y, 1, N);
    free_vector(Temp, 1, N);

    return 0;
}




double Mskalarne(float *A, float *B, int n){
    int i;
    double suma=0.;
    for(i=1 ; i<=n ; i++){
        suma += A[i] * B[i];
    }
    return suma;
}

double norma(float *r, int n){
	return sqrt(Mskalarne(r, r, n));
}


void mnozMacierzVektor(int n, float ** A, float *x, float *wynik, int m){
	int i, j;

	for (i = 0; i < n; i++){
		wynik[i+1] = 0.0;
		for (j = max(0, i - m); j <= min(n - 1, i + m); j++)
			wynik[i+1] += A[i+1][j+1] * x[j+1];
	}
}