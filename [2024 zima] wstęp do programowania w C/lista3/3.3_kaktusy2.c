// wejscie: n, m, v, t.z. n, m, v ≤ 2×10^6, n < m, 0 ≤ v
// wyjscie: min(x + y - z) > v
// x, y, z = liczby primes w przedziale [n, m] zawierajace jednoczesnie 3 i 7

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 2000000
int primes[MAX + 1] = {};
int validPrimes[1000000] = {};

int contains3and7(int num);
void sieve(int *primes, int n, int m);

int main(void)
{
    // wczytanie zmiennych
    int n, m, v;
    scanf("%d%d%d", &n, &m, &v);

    // szukanie liczb pierwszych w przedziale [n, m]
    sieve(primes, n, m);

    // zapisywanie tylko liczb pierwszych zawierajach 3 i 7
    int count = 0;
    for (int i = 0; i < (m - n + 1); i++)
    {
        if (primes[i] == 0 && contains3and7(i + n))
        {
            validPrimes[count] = (i + n);
            count++;
        }
    }

    // wypisanie znalezionych liczb pierwszych z 3 i 7
    for (int i = 0; i < count; i++)
       printf("%d ", validPrimes[i]);
    printf("\n");

    // szukanie min(x + y - z) > v
    int min_value = INT_MAX;
    int p_x, p_y, result;
    for (int p_z = 2; p_z < count; p_z++)
    {
        // szukanie z dwoma pointerami
        p_x = 0;
        p_y = count - 1;

        while (p_x < p_y)
        {
            result = validPrimes[p_x] + validPrimes[p_y] - validPrimes[p_z];
            if (result > v)
            {
                if (result < min_value) min_value = result;
                p_y--;
            }
            else p_x++;
        }
    }
    printf("%d", min_value);
    return 0;
}

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

    if (n == 1) primes[0] = 1;
}

int contains3and7(int num)
{
    bool has3 = false, has7 = false;
    int digit = 0;
    
    while (num > 0)
    {
        // izolujemy i sprawdzamy ostatnia cyfre
        digit = num % 10;
        num /= 10;

        if (digit == 3) has3 = true;
        else if (digit == 7) has7 = true;
        if (has3 && has7) return 1;
    }
    return 0;
}
