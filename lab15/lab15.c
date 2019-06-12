#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"

#define frand() ((double)rand()) / (RAND_MAX + 1.0)

double norma(double *vec1, double *vec2);
double *rozVec(double *vec1, double *vec2);
double skalarny(double *vec1, double *vec2);
int theta(double x, double y, double z, double xmin, double ymin, double zmin, double xmax, double ymax, double zmax);

int main()
{
    double rho = 1.0;

    //V
    double a = 4.0;
    double v_xmin, v_ymin, v_zmin;
    double v_xmax, v_ymax, v_zmax;
    v_xmin = v_ymin = v_zmin = -2.0;
    v_xmax = v_ymax = v_zmax = 2.0;

    //omega
    double b = 2.0;
    double o_xmin, o_ymin, o_zmin;
    double o_xmax, o_ymax, o_zmax;
    o_xmin = o_ymin = o_zmin = -1.0;
    o_xmax = o_ymax = o_zmax = 1.0;

    //1.
    double *R1 = dvector(1, 3);
    double *R2 = dvector(1, 3);
    R1[1] = R1[2] = R1[3] = -1.0;
    R2[1] = R2[2] = R2[3] = 1.0;

    FILE *zad1;
    zad1 = fopen("zad1.dat", "a");

    int N = pow(10, 6);
    double I = 0.0;
    double sigma;
    double sigma1 = 0.0;
    double sigma2 = 0.0;
    double s;

    for (int i = 1; i <= N; i++)
    {
        double *Ri = dvector(1, 3);
        Ri[1] = frand() * 4 - 2;
        Ri[2] = frand() * 4 - 2;
        Ri[3] = frand() * 4 - 2;
        double ri = sqrt((skalarny(rozVec(R1, Ri), rozVec(R1, Ri)) * skalarny(rozVec(R2, R1), rozVec(R2, R1)) - pow(skalarny(rozVec(R1, Ri), rozVec(R2, R1)), 2)) / (skalarny(rozVec(R2, R1), rozVec(R2, R1))));
        I += pow(a, 3) * rho * pow(ri, 2) * theta(Ri[1], Ri[2], Ri[3], o_xmin, o_ymin, o_zmin, o_xmax, o_ymax, o_zmax);
        sigma1 += pow(pow(a, 3) * rho * pow(ri, 2) * theta(Ri[1], Ri[2], Ri[3], o_xmin, o_ymin, o_zmin, o_xmax, o_ymax, o_zmax), 2);
        sigma2 = pow(I, 2);
        sigma2 /= i;
        sigma = (1.0 / i) * (sigma1 - sigma2);
        s = sqrt(sigma / i);

        if ((i % 1000) == 0)
            fprintf(zad1, "%d %15g %15g\n", i, (I / i), s);
    }


    //2.
    R1[1] = R1[2] = R1[3] = R2[1] = R2[2] = 1.0;
    R2[3] = -1.0;
    I = sigma = sigma1 = sigma2 = 0.0;
    FILE *zad2;
    zad2 = fopen("zad2.dat", "a");
    for (int i = 1; i <= N; i++)
    {
        double *Ri = dvector(1, 3);
        Ri[1] = frand() * 4 - 2;
        Ri[2] = frand() * 4 - 2;
        Ri[3] = frand() * 4 - 2;
        double ri = sqrt((skalarny(rozVec(R1, Ri), rozVec(R1, Ri)) * skalarny(rozVec(R2, R1), rozVec(R2, R1)) - pow(skalarny(rozVec(R1, Ri), rozVec(R2, R1)), 2)) / (skalarny(rozVec(R2, R1), rozVec(R2, R1))));
        I += pow(a, 3) * rho * pow(ri, 2) * theta(Ri[1], Ri[2], Ri[3], o_xmin, o_ymin, o_zmin, o_xmax, o_ymax, o_zmax);
        sigma1 += pow(pow(a, 3) * rho * pow(ri, 2) * theta(Ri[1], Ri[2], Ri[3], o_xmin, o_ymin, o_zmin, o_xmax, o_ymax, o_zmax), 2);
        sigma2 = pow(I, 2);
        sigma2 /= i;
        sigma = (1.0 / i) * (sigma1 - sigma2);
        s = sqrt(sigma / i);

        if ((i % 1000) == 0)
            fprintf(zad2, "%d %15g %15g\n", i, (I / i), s);
    }
	
	fclose(zad1);
	fclose(zad2);
	free_dvector(R1, 1, 3);
	free_dvector(R2, 1, 3);
	
    return 0;
}

int theta(double x, double y, double z, double xmin, double ymin, double zmin, double xmax, double ymax, double zmax)
{
    if (x <= xmax && x >= xmin)
        if (y <= ymax && y >= ymin)
            if (z <= zmax && z >= zmin)
                return 1;
    return 0;
}

double *rozVec(double *vec1, double *vec2)
{
    double *vec_wyn = dvector(1, 3);
    vec_wyn[1] = vec1[1] - vec2[1];
    vec_wyn[2] = vec1[2] - vec2[2];
    vec_wyn[3] = vec1[3] - vec2[3];
    return vec_wyn;
}

double skalarny(double *vec1, double *vec2)
{
    return (vec1[1] * vec2[1] + vec1[2] * vec2[2] + vec1[3] * vec2[3]);
}

double norma(double *vec1, double *vec2)
{
    return sqrt(skalarny(vec1, vec2));
}
