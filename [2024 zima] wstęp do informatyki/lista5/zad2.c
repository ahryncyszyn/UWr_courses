#include <stdio.h>

// Wejscie: n - liczba naturalna
// Wyjście: silniowa reprezentacja n = ciag  wspolczynnikow s1, ..., sk, t.z.:
// n = 1! · s1 + 2! · s2 + · · · + k! · sk,
// si ≤ i dla każdego i ∈ {1, 2, . . . , k},
// sk ̸= 0.

// O(1)

void silniowaReprezentacja(int n);

int main(void)
{
    int n;
    printf("Podaj liczbe naturalna n\n");
    scanf("%d", &n);
    silniowaReprezentacja(n);

    return 0;
}

// O(log(n))
// dowod:
// dla s > 4 zachodzi s! > 2^s
// log(s!) > log(2^s) = s
// 2^(s-1) < (s-1)! < n < s!4444e
// s - 1 < log(n)
void silniowaReprezentacja(int n)
{
    long long silnia = 1; // obecna obliczona silnia
    int s = 1;

    // zwiekszamy silnie az bedzie wieksza od n
    while (silnia <= n) 
    {
        s++;
        silnia *= s;
    }

    silnia /= s;
    s--;

    while (s > 0)
    {
        printf("%lld ", n / silnia);
        n %= silnia;
        silnia = silnia / s;
        s--;
    }
    printf("\n");
}
