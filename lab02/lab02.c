#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "nrutil.c"
#include "lubksb.c"
#include "ludcmp.c"


#define N 3

void wypelnij(float **A){
    A[1][1]=1;  A[1][2]=2;  A[1][3]=3;
    A[2][1]=4;  A[2][2]=5;  A[2][3]=6;
    A[3][1]=7;  A[3][2]=8;  A[3][3]=9;
}

void wypisz_macierz(float **A, FILE *plik){
    int i,j;
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++)
            fprintf(plik,"%15g ",A[i][j]);
        fprintf(plik,"\n");
    }
    fprintf(plik,"\n");    
}

int main(){
    int i,j;
    float d;

    float **A;
    float **B;
    float **A_odw;
    float **B_odw;
    int *indx_a;
    int *indx_b;
    float *x_a;             //wektor rozwiazania
    float *x_b;
    float **A_iloczyn;
    float **B_iloczyn;


    FILE *plik;

    plik=fopen("wyniki.dat","w");
    
    A = matrix(1,N,1,N); //alokacja macierzy A
    B = matrix(1,N,1,N); //alokacja macierzy B
    A_odw = matrix(1,N,1,N); //alokacja macierzy odwrotnej A_odw
    B_odw = matrix(1,N,1,N); //alokacja macierzy odwrotnej B_odw
    indx_a=ivector(1,N);
    indx_b=ivector(1,N);
    x_a=vector(1,N);
    x_b=vector(1,N);
    A_iloczyn = matrix(1,N,1,N);
    B_iloczyn = matrix(1,N,1,N);

    wypelnij(A);
    wypelnij(B);
    B[1][1]=1.1;

    fprintf(plik, "Macierz A:\n");
    wypisz_macierz(A, plik);


    fprintf(plik, "\nMacierz B:\n");
    wypisz_macierz(B, plik);

    //1.Rozklad macierzy A i B

    ludcmp(A, N, indx_a, &d);
    ludcmp(B, N, indx_b, &d);

    fprintf(plik, "Rozklad macierzy A:\n");
    wypisz_macierz(A, plik);


    fprintf(plik,"\nRozklad macierzy B:\n");
    wypisz_macierz(B,plik);

    //2.Macierze odwrotne
    
    for(i=1;i<=N;i++){
        x_a[1]=0;   x_a[2]=0;   x_a[3]=0;
        x_b[1]=0;   x_b[2]=0;   x_b[3]=0;    

        x_a[i]=1;
        x_b[i]=1;
                    lubksb(A,N,indx_a,x_a);
            lubksb(B,N,indx_b,x_b);
        for(j=1;j<=N;j++){

            A_odw[j][i]=x_a[j];
            B_odw[j][i]=x_b[j];
        }
    }

    fprintf(plik, "Rozklad macierzy odwrotnej A:\n");
    wypisz_macierz(A_odw, plik);


    fprintf(plik,"\nRozklad macierzy odwrotnej B:\n");
    wypisz_macierz(B_odw,plik);

    //3. Wskaznik uwarunkowania
    float a_max=0;
    float b_max=0;
    float a_odw_max=0;
    float b_odw_max=0;
    
    wypelnij(A);
    wypelnij(B);
    B[1][1]=1.1;

    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++){
            if( a_max < fabs(A[i][j]) ) a_max=fabs(A[i][j]);
            if( b_max < fabs(B[i][j]) ) b_max=fabs(B[i][j]);
            if( a_odw_max < fabs(A_odw[i][j]) ) a_odw_max=fabs(A_odw[i][j]);
            if( b_odw_max < fabs(B_odw[i][j]) ) b_odw_max=fabs(B_odw[i][j]);            
        }
    
    fprintf(plik, "\nWskaznik uwarunkowania macierzy A: %g\n",a_max);
    fprintf(plik, "\nWskaznik uwarunkowania macierzy B: %g\n",b_max);
    fprintf(plik, "\nWskaznik uwarunkowania macierzy odwrotnej A: %g\n",a_odw_max);
    fprintf(plik, "\nWskaznik uwarunkowania macierzy odwrotnej B: %g\n",b_odw_max);
    fprintf(plik, "\nKappa A: %g\n",a_max*a_odw_max);
    fprintf(plik, "\nKappa B: %g\n",b_max*b_odw_max);

    //4. Iloczyny

    for (i=1;i<=N;i++)
        for(j=1;j<=N;j++){
            A_iloczyn[i][j]=0;
            B_iloczyn[i][j]=0;            
            for(int k=1;k<=N;k++){
                A_iloczyn[i][j]+=A[i][k]*A_odw[k][j];
                B_iloczyn[i][j]+=B[i][k]*B_odw[k][j]; 
            }
        }
    
    fprintf(plik, "\n\nIloczyn A i A_odw:\n");
    wypisz_macierz(A_iloczyn, plik);


    fprintf(plik,"\nIloczyn B i B_odw:\n");
    wypisz_macierz(B_iloczyn,plik);

    fclose(plik);
    free_matrix(A,1,N,1,N);
    free_matrix(B,1,N,1,N);
    free_matrix(A_odw,1,N,1,N);
    free_matrix(B_odw,1,N,1,N); 
    free_ivector(indx_a,1,N);
    free_ivector(indx_b,1,N);
    free_vector(x_a,1,N);
    free_vector(x_b,1,N);
    free_matrix(A_iloczyn,1,N,1,N);
    free_matrix(B_iloczyn,1,N,1,N);

    return 0;
}