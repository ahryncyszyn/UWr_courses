// Aleksandra Hryncyszyn, 353636
// lista 4, zad 1

#include <stdio.h>
#include <stdlib.h>

double ntyWyraz(int n, int k, double *a, double *f);

int main(int argc, char *argv[])
{
    printf("argc to %d\n", argc);

    // wczytanie parametru k
    int k = atoi(argv[1]);

    // zweryfikowanie liczby argumentow
    if (argc != 2*k + 2)
    {
        printf("Niepoprawna liczba argumentow\n");
        return 1;
    }

    // wczytanie tablicy a[k]
    double a[k];
    for (int i = 2; i < 2 + k; i++)
    {
        a[i - 2] = atof(argv[i]);
    }

    // wczytanie tablicy f[k]
    double f[k];
    for (int i = 2 + k; i < 2 * k + 2; i++)
    {
        f[i - k - 2] = atof(argv[i]);
    }

    // wczytanie parametru n
    int n = -1;
    while (n < 0 || n < k)
    {
        printf("Podaj nieujemna liczbe n >= k\n");
        while (scanf("%d", &n) < 1) getchar();
    }

    // wywolanie funkcji rekurencyjnej
    double result = 0.0;
    result = ntyWyraz(n, k, a, f);
    printf("N-ty wyraz podanego ciagu to: %lf\n", result);

    return 0;
}

double ntyWyraz(int n, int k, double *a, double *f)
{
    if (n < k) return f[n];

    double result = 0.0;
    for (int i = 1; i <= k; i++)
    {
        result += a[i-1] * ntyWyraz(n-i, k, a, f);
    }

    return result;
}
