#include <stdio.h>

// ((a mod r) + (b mod r)) mod r = (a + b) mod r
// a = r * q1 + r1, wiec a mod r = r1
// b = r * q2 + r2, wiec b mod r = r2
// P: (a + b) mod r = (r * (q1 + q2) + r1 + r2) mod r = (r1 + r2) mod r
// L: ((a mod r) + (b mod r)) mod r = (r1 + r2) mod r

// Wejście: k, r - liczby calkowite
// Wyjście: F_{k} mod r
// liczby tylko mniejsze od 2max(k, r)

int fibMod(int k, int r)
{
    if (k == 0) return 0;

    if (k == 1) return 1 % r;

    int prev1 = 0;   // F_0 mod r
    int prev2 = 1;   // F_1 mod r
    int current;

    for (int i = 2; i <= k; i++) 
    {
        current = (prev1 + prev2) % r;
        prev1 = prev2;
        prev2 = current;
    }

    return current;
}

int main(void)
{
    int k = 5, r = 1;
    printf("wynik to: %d\n", fibMod(k, r));
    return 0;
}
