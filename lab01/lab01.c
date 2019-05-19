#include <stdio.h>
#include <stdlib.h>
#include <math.h>

z


#define N 400 // rozmiar macierzy A: NxN

int main(void) {
	float **A,**b;
	FILE *plik;
	int k,m,omega,v,a;
	float h;
	a=1;
	h=0.1;
	v=0;
	omega=1; //poniewaz omega^2=k/m=1;


//	Alokacja macierzy
	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);
	
// 	Wypelnienie macierzy A i wektora b zerami
	for(int i=1; i<=N; ++i){
		b[i][1] = 0.0;
		for(int j=1; j<=N; ++j)
			A[i][j] = 0.0;
	}

	b[1][1]=a;
	b[2][1]=v*h;
	
	for(int i=1; i<=N ;++i){
		for(int j=1 ; j<=N ; ++j){
			if(i==j)			//1 na glownej przekatnej
				A[i][j]= 1.0;	
			if( j == (i-2) )	//1 dwie pozycje pod przekatna
				A[i][j]= 1.0;
			if( j == (i-1) )	//liczby pod przekatna
				if(i == 2 && j == 1)
					A[i][j] = -1.0;
				else
					A[i][j] = omega*omega*h*h-2;
		}
	}
	
//	Rozwiazanie ukladu rownan Ax=b - wywolanie procedury:
	gaussj(A,N,b,1);

	plik = fopen("out.dat","w");

//	Wypisanie rozwiazania, ktore procedura gaussj(A,N,b,1); zapisala w wektorze b.
	for(int i=1; i<=N; ++i)
		fprintf(plik,"%g %g\n",(i-1)*h,  b[i][1]); 
    
//	Zwolnienie pamieci
	free_matrix(A,1,N,1,N);
	free_matrix(b,1,N,1,1);    
	
	return 0;
}
