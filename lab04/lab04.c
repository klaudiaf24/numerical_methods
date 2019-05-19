#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_eigen.h>

void setMatrix(gsl_matrix *a, gsl_matrix *b, int size, int dlStruny, int naciag, int alfa);
int delta (int x, int y);

int main(){
    int i,j;
    FILE *plik;
    FILE *plik2;
    FILE *plik3;
    FILE *plik4;

    
//  1.
    int L = 10;
    int n = 200;    //rozmiar problemu
    int N = 1;      //naciag
    int alfa = 0;
    
//  2.
    gsl_matrix *A = gsl_matrix_calloc(n,n);
    gsl_matrix *B = gsl_matrix_calloc(n,n);
    
    setMatrix(A,B,n,L,N,alfa);
    
    plik = fopen("wyniki.dat", "w");

    fprintf(plik,"Macierz A\n");
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j ++)
            fprintf(plik,"%3g ", gsl_matrix_get(A,i,j));
        fprintf(plik,"\n");        
        }

    fprintf(plik,"\nMacierz B\n");
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j ++)
            fprintf(plik,"%3g ", gsl_matrix_get(B,i,j));
        fprintf(plik,"\n");        
    }

// 3. i 4.
    gsl_vector *eval = gsl_vector_alloc(n);
    gsl_matrix *evec = gsl_matrix_alloc(n, n);
    gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);


    plik2 = fopen("wart_alfa.dat","w");
    plik3 = fopen("wektory_wlasne_0.dat", "w");
    plik4 = fopen("wektory_wlasne_100.dat", "w");

    fprintf(plik2,"Wartosci wlanse\n");

    for(i = 0 ; i <= 100 ; i += 2){
        setMatrix(A,B,n,L,N,i);
        gsl_eigen_gensymmv(A, B, eval, evec, w);
        gsl_eigen_sort_t sort_type = GSL_EIGEN_SORT_ABS_ASC;
        gsl_eigen_gensymmv_sort(eval, evec, sort_type);        
        
        
        fprintf(plik2,"%d\t", i);
        for(j = 0 ; j < 6 ; j++)
            fprintf(plik2,"%10g\t", sqrt(gsl_vector_get(eval,j)));
        fprintf(plik2,"\n");

        //alfa = 0
        if (i == 0) {
            double deltaX = (double)L / (n + 1.);
            
            for( int k = 0 ; k < n ; k++) { // Numer punktu x_i
                double x_i = -L/2. + deltaX*(k+1.);
                fprintf(plik3,"%10g\t", x_i);
                
                for(j = 0 ; j < 6 ; j++) // Numer wektora wlasnego
                    fprintf(plik3,"%10g\t", (gsl_matrix_get(evec,k,j)));
                fprintf(plik3,"\n");
            }
        }


        //alfa = 100
        if (i == 100) {
            double deltaX = (double)L / (n + 1.);
            
            for(int k = 0 ; k < n ; k++) { // Numer punktu x_i
                double x_i = -L/2. + deltaX*(k+1.);
                fprintf(plik4,"%10g\t", x_i);
                
                for(j = 0 ; j < 6 ; j++) // Numer wektora wlasnego
                    fprintf(plik4,"%10g\t", (gsl_matrix_get(evec,k,j)));
                fprintf(plik4,"\n");
            }

        }
    }



    fclose(plik);
    fclose(plik2);
    fclose(plik3);
    fclose(plik4);

    gsl_matrix_free(A);
    gsl_matrix_free(B);
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    gsl_eigen_gensymmv_free(w);

    return 0;
}


void setMatrix(gsl_matrix *a, gsl_matrix *b, int size, int dlStruny, int naciag, int alfa){
    int i,j;
    double temp1, temp2;
    double deltaX, ro;

    for(i = 0 ; i < size ; i++)
        for(j = 0 ; j < size ; j++){

            //Macierz A
            deltaX = (double)dlStruny / (size + 1.);
            temp1 = (-delta(i, j+1) + 2 * delta(i, j) - delta(i, j-1) ) / pow(deltaX,2);
            gsl_matrix_set(a,i,j,temp1);
            
            //Macierz B
            ro = 1 + 4 * alfa * pow( -dlStruny/2 + deltaX*(i+1),2 ) ;
            temp2 = ( ro * delta(i,j) ) / naciag;
            gsl_matrix_set(b,i,j,temp2);
        }



}

int delta (int x, int y){
    if (x == y)
        return 1;
    else
        return 0;
}