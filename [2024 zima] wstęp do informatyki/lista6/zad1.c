#include <stdio.h>

int zla_funkcja(int a[], int i)
{
    int x = a[i];
    int lewy = 0; 
    int prawy = i - 1;
    int k;

    while (lewy < prawy) 
    {
        k = (lewy + prawy) / 2; // 1/2 = 0
        if (a[k] < x) lewy = k; // blad bo wartosc lewego sie nie zmienia
        else prawy = k;
    }
    return lewy;
}

int poprawna_funkcja(int a[], int i)
{
    int x = a[i];
    int lewy = 0; 
    int prawy = i - 1;
    int k;

    while (lewy <= prawy) 
    {
        k = (lewy + prawy) / 2; // 1/2 = 0
        if (a[k] < x) lewy = k + 1;
        else prawy = k - 1;
    }
    return lewy;
}

int main(void) 
{
    int a[] = {1, 2, 3, 4, 9};
    int i = 4;
    printf("%d", poprawna_funkcja(a, i));

    return 0;
}