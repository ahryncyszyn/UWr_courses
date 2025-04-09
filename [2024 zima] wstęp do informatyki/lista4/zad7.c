#include <stdio.h>
// Wejście: n - liczba naturalna
// Wyjście: k - liczba roznych cyfr w dziesietnym zapisie n


int main(void)
{
    int n, k = 0, cyfra;
    printf("Podaj liczbe naturalna do sprawdzenia\n");
    scanf("%d", &n);
    int liczby[10] = {0};

    while (n > 0)
    {
        cyfra = n % 10;
        if (liczby[cyfra] == 0)
        {
            liczby[cyfra] = 1;
            k++;
        }
        n = n / 10;
    }

    printf("Liczba n ma zapis %d-cyfrowy\n", k);
    return 0;
}