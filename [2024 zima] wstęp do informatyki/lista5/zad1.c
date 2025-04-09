#include <stdio.h>
// Wejście: k - liczba naturalna
// Wyjście: wartosc b_max/b_min nalezacego do [2^k, 2^(k+1)] dla ktorego algorytm 
// szybkiego potegowania wykona najwiecej/najmniej mnozen

// mnozenie 1 jezeli wykladnik jest parzysty, 2 jezeli nieparzysty
// k = 10, limit to [1024, 2048]
// najwiecej mnozen: 2047 (22), najmniej: 1024 (12)

// zloz. czas = 
// zloz. pam = 

int potR(long long a, int b, int *mnozenia)
{
    if (b == 0) return 1;
    
    if (b % 2 == 1) {
        (*mnozenia) += 2;
        return a * potR(a * a, b / 2, mnozenia);
    } else {
        (*mnozenia) += 1;
        return potR(a * a, b / 2, mnozenia);
    }
}

int potI(long long a, int b, int *mnozenia)
{
    long long rez = 1;
    printf("Rez w wersji iteracyjnej: ");
    printf("%lld ", rez);
    while (b > 0)
    {
        if (b % 2 == 1) 
        {
            rez = rez * a;
            printf("%lld ", rez);
            (*mnozenia) += 1;
        }
        b = b / 2;
        a = a * a;
        (*mnozenia) += 1;
    }
    printf("\n");
    return rez;
}

void minmaxMnozen(long long a, int b, int k)
{
    int minM = 1, maxM;
    for (int i = 1; i <= k; i++)
        minM *= 2;
    maxM = minM * 2 - 1;
    printf("Dla k = %d, maksymalna liczba mnozen jest dla b = %d, a minimalna dla b = %d\n", k, maxM, minM);

    int mnozeniaR = 0, mnozeniaI = 0;
    potR(a, b, &mnozeniaR);
    potI(a, b, &mnozeniaI);
    printf("Liczba mnozen dla wersji rekurencyjnej to %d, a dla iteratywnej to %d\n", mnozeniaR, mnozeniaI);

}

int main(void) 
{
    long long a;
    int b, k;
    printf("Podaj trzy liczby naturalne a, b, k\n");
    scanf("%lld%d%d", &a, &b, &k);

    minmaxMnozen(a, b, k);
    return 0;
}