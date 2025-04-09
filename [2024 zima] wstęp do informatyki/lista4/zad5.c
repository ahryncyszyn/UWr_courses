#include <stdio.h>
// Wejście: n - liczba naturalna
// Wyjście: "TAK", jezeli n jest palindromem binarnym
//          "NIE", jezeli nie jest


int main(void)
{
    int n;
    printf("Podaj liczbe naturalna\n");
    scanf("%d", &n);
    int bin[32];
    int i = 0;

    while (n > 0)
    {
        bin[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = 0; j < i / 2; j++)
    {
        if (bin[j] != bin[i - j - 1])
        {
            printf("Liczba ta nie jest palindromem binarnym\n");
            return 0;
        }
    }
    printf("Liczba ta jest palindromem binarnym\n");
    return 0;
}