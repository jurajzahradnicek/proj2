#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

double taylor_log(double x, unsigned int n);
//double taylorcf_pow(double x, double y, unsigned int n);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        if (strcmp(argv[1], "--log") == 0) {
            double x = strtod(argv[2], NULL);
            unsigned long int n = strtoul(argv[3], NULL, 10);
            if (x <= 0.0) {
                printf("Logaritmus nie je definovany\n");
            } else {
                printf("taylor_log = %.12g\n", taylor_log(x, n));
            }
        } else return 0;
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

/*double taylorcf_pow(double x, double y, unsigned int n)
{

}*/