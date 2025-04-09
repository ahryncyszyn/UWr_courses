#include <stdio.h>

void sieve(int *primes, int n, int m)
{
    for (int i = 2; i*i <= m; i++)
    {
        // znajdujemy najmniejsza wielokrotnosc i wieksza od n
        int start = ((n + i - 1) / i) * i;

        // jezeli jest mniejsza niz i*i to zmieniamy na i*i
        // bo liczby mniejsze od i*i zostaly juz wykreslone przez mniejsze i
        if (start < i * i) start = i * i;

        // wykreslamy wszystkie wielokrotnosci i wieksze od n
        for (int j = start; j <= m; j += i)
        {
            if (j >= n) 
            {
                primes[j - n] = 1; 
            }
        }
    }

    if (n == 1) primes[0] = 0;
}

int main(void)
{

    int n = 100, m = 200;
    int primes[m - n + 1] = {};
    sieve(primes, n, m);
    return 0;
}