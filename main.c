/* Juraj Zahradnicek - xzahra31
 * projekt 2 - Interacni vypocty
 * FIT VUT / BIT1 - 2018/2019 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

double taylor_log(double x, unsigned int n);                                   //deklaracia vsetkych pouzitych funkcii
double cfrac_log(double x, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        if (strcmp(argv[1], "--log") == 0) {                                   //podmienka pre argument (splni sa pri zadani --log)
            double x = strtod(argv[2], NULL);                                  //deklaracia premennych, zadavame z argumentov
            unsigned long int n = strtoul(argv[3], NULL, 10);
            if (x <= 0.0) {                                                    //osetrenie logaritmu v intervale, v ktorom nie je definovany
                printf("Logaritmus nie je definovany\n");
            } else {                                                           //vypis a volanie jednotlivych funkcii pre logaritmus
                printf("       log(%.4g) = %.12g\n",x, log(x));
                printf(" cfrac_log(%.4g) = %.12g\n",x,cfrac_log(x, n));
                printf("taylor_log(%.4g) = %.12g\n",x, taylor_log(x, n));
            }


        }
        else if (strcmp(argv[1], "--pow") == 0){                               //podmienka pre argument (splni sa pri zadani --pow)
            double x = strtod(argv[2], NULL);                                  //deklaracia premennych, zadavame z argumentov
            double y = strtod(argv[3], NULL);
            unsigned long int n = strtoul(argv[4], NULL, 10);
            if(x == 1 || y == 0){                                              //osetrenie mocniny (netrapi sa s vypoctom, ale rovno vypise 1)
                printf("         pow(%g ,%g) = 1\n",x,y);
                printf("  taylor_pow(%g ,%g) = 1\n",x,y);
                printf("taylorcf_pow(%g ,%g) = 1\n",x,y);
            }
            else{                                                              //vypis a volanie jednotlivych funkcii pre mocniny
                printf("         pow(%g ,%g) = %.12g\n",x,y,pow(x,y));
                printf("  taylor_pow(%g ,%g) = %.12g\n",x,y,taylor_pow(x,y,n));
                printf("taylorcf_pow(%g ,%g) = %.12g\n",x,y,taylorcf_pow(x,y,n));
            }
        }
        else                                                                   //vypis pre zle zadane argumenty
            printf("Nespravne zadany argument\n");
    }
    return 0;
}

double taylor_log(double x, unsigned int n)                                   //funkcia taylor_pow - pouzitie taylorovho polynomu
{
    double vysledok = 0.0;                                                    //premenna vysledok naplnena nulou na zaciatku funkcie
    if(x < 1.0) {                                                             //vypocet logaritmu pomocou taylorovho polynomu v intervale od 0 po 1
        double yn = 1.0;
        for (unsigned int i = 1; i <= n; i++) {
            double y = 1 - x;                                                 //definicia y po upraveni povodnej rovnice
            yn *= y;
            vysledok -= yn / i;
        }
    }
    else{                                                                    //vypocet logaritmu pomocou taylorovho polynomu v intervale od 0 po nekonecno
        double y = (x - 1) / x;                                              //definicia y po upraveni povodnej rovnice
        double xn = 1.0;
        for (unsigned int i = 1; i <= n; i++){
            xn = xn * y;
            vysledok += xn / i;
        }
    }
    return vysledok;                                                         //navratova hodnota vysledok po vypocitani logaritmu
}

double cfrac_log(double x, unsigned int n)                                   //funkcia cfrac_log - pouzitie zretazenych zlomkov
{
     x = (x-1) / (x+1);                                                      //vyjadrenie x z definicie povodnej rovnice
     double vysledok = 0.0;                                                  //deklaracia premennych pre funkciu
     double xn = 0.0;
     for (unsigned int i = n; i >= 1 ; i--) {
        xn =(-(i*i*x*x) / ((2*i+1)+xn));
        vysledok = (2*x) / (1+xn);
     }
    return vysledok;                                                         //navratova hodnota vysledok
}

double taylor_pow(double x, double y, unsigned int n)                        //funcia tayor_pow - vypocet mocniny s pouzitim logaritmu pocitaneho pomocou taylorovho polynomu
{
    double vysledok = 1.0;                                                   //deklaracia premennych pre funkciu
    double yn = 1.0;
    double ln = taylor_log(x, n);                                            //volanie funkcie taylor_log
    double fact = 1.0;

    for(unsigned int i = 1; i<=n; i++)
    {
        fact *= i;
        yn *=y;
        vysledok += (yn*ln) / fact;
        ln *= taylor_log(x, n);
    }
    return vysledok;                                                        //navratova hodnota vysledok
}

double taylorcf_pow(double x, double y, unsigned int n)                     //funkcia taylorcf_pow - vypocet mocniny s pouzitim logaritmu pocitaneho pomocou zretazenych zlomkov
{
    double vysledok = 1.0;                                                  //deklaracia premennych pre funkciu
    double yn = 1.0;
    double ln = cfrac_log(x,n);                                             //volanie funkcie cfrac_log
    double fact = 1.0;

    for(unsigned int i = 1; i<=n; i++)
    {
        fact *= i;
        yn *= y;
        vysledok += (yn*ln) / fact;
        ln *= cfrac_log(x,n);
    }
    return vysledok;                                                        //navratova hodnota vysledok
}
