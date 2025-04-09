#include <stdio.h>

// Wejscie: n - liczba naturalna
// Wyjscie: G(n), gdzie:
// G0 = G1 = G2 = 1,
// Gn = Gn−1 + Gn−2 + Gn−3 dla n ≥ 3

int gn(int n)
{
    if (n < 3) return 1;

    int G0 = 1, G1 = 1, G2 = 1, Gn;

    for (int i = 3; i < n + 1; i++)
    {
        Gn = G0 + G1 + G2;
        G0 = G1;
        G1 = G2;
        G2 = Gn;
    }
    return Gn;
}

int main(void)
{
    int n = 6;
    printf("wynik to: %d\n", gn(n));
    return 0;
}