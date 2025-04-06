// Aleksandra Hryncyszyn, 353636
// zad 2, lista 5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("za duzo argumentow wywolania\n");
        return 1;
    }
    
    // wczytanie argumentu n
    int n;
    if (argc == 1) n = 80;
    else n = atoi(argv[1]);

    // wypisanie kolejnych wartości funkcji
    printf("%d\n", n);
    double wartosc;
    for (float i = 0.0; i < n; i++)
    {
        wartosc = 5*sin(i) + 15*cos(i/10);
        printf("%.2f ", wartosc);
    }
}