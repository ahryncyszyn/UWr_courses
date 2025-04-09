#include <stdio.h>
// Wejście: n - liczba naturalna
//          k - podstawa systemu liczbowego w jakim sprawdzamy palindromicznosc
// Wyjście: "TAK", jezeli n jest palindromem k-arnym
//          "NIE", jezeli nie jest


int main(void) // O(logk(n))
{
    int n, k;
    printf("Podaj liczbe naturalna do sprawdzenia\n");
    scanf("%d", &n);
    printf("Podaj liczbe k, bedaca podstawa systemu liczbowego\n");
    scanf("%d", &k);
    int repr[32];
    int i = 0;

    while (n > 0)
    {
        repr[i] = n % k;
        printf("%d ", repr[i]);
        n = n / k;
        i++;
    }

    for (int j = 0; j < i / 2; j++)
    {
        if (repr[j] != repr[i - j - 1])
        {
            printf("Liczba ta nie jest palindromem binarnym\n");
            return 0;
        }
    }
    printf("Liczba ta jest palindromem binarnym\n");
    return 0;
}