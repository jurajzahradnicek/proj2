#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        if (strcmp(argv[1], "--log") == 0) {
            double x = strtod(argv[2], NULL);
            unsigned long int n = strtoul(argv[3], NULL, 10);
            if (x <= 0.0) {
                printf("Logaritmus nie je definovany\n");
            } else {
                printf("       log(%.4g) = %.12g\n",x, log(x));
                printf(" cfrac_log(%.4g) = %.12g\n",x,cfrac_log(x, n));
                printf("taylor_log(%.4g) = %.12g\n",x, taylor_log(x, n));
            }
        }
        if (strcmp(argv[1], "--pow") == 0){
            double x = strtod(argv[2], NULL);
            double y = strtod(argv[3], NULL);
            unsigned long int n = strtoul(argv[4], NULL, 10);
            if(x == 1 || y == 0){
                printf("         pow(%g ,%g) = 1\n",x,y);
                printf("  taylor_pow(%g ,%g) = 1\n",x,y);
                printf("taylorcf_pow(%g ,%g) = 1\n",x,y);
            }
            else{
                printf("         pow(%g ,%g) = %.12g\n",x,y,pow(x,y));
                printf("  taylor_pow(%g ,%g) = %.12g\n",x,y,taylor_pow(x,y,n));
                printf("taylorcf_pow(%g ,%g) = %.12g\n",x,y,taylorcf_pow(x,y,n));
            }
        }
    }
    return 0;
}

double taylor_log(double x, unsigned int n)
{
    double vysledok = 0.0;
    if(x < 1.0) {
        double yn = 1.0;
        for (unsigned int i = 1; i <= n; i++) {
            double y = 1 - x;
            yn *= y;
            vysledok -= yn / i;
        }
    }
    else{
        double y = (x - 1) / x;
        double xn = 1.0;
        for (unsigned int i = 1; i <= n; i++){
            xn = xn * y;
            vysledok += xn / i;
        }
    }
    return vysledok;
}

double cfrac_log(double x, unsigned int n)
{
     x = (x-1) / (x+1);
     double vysledok = 0.0;
     double xn = 0.0;
     for (unsigned int i = n; i >= 1 ; i--) {
        xn =(-(i*i*x*x) / ((2*i+1)+xn));
        vysledok = (2*x) / (1+xn);
     }
    return vysledok;
}

double taylor_pow(double x, double y, unsigned int n)
{
    double vysledok = 1.0;
    double yn = 1.0;
    double ln = taylor_log(x, n);
    unsigned int fact = 1;

    for(unsigned int i = 1; i<=n; i++)
    {
        fact *= i;
        yn *=y;
        vysledok += (yn*ln) / fact;
        ln *= taylor_log(x, n);
    }
    return vysledok;
}

double taylorcf_pow(double x, double y, unsigned int n)
{
    double vysledok = 1.0;
    double yn = 1.0;
    double ln = cfrac_log(x,n);
    unsigned int fact = 1;

    for(unsigned int i = 1; i<=n; i++)
    {
        fact *= i;
        yn *= y;
        vysledok += (yn*ln) / fact;
        ln *= cfrac_log(x,n);
    }
    return vysledok;
}