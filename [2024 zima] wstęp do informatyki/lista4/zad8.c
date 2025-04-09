#include <stdio.h>
// Wejście: n, m - liczby naturalne
// Wyjście: "TAK", jezeli liczby maja taka sama liczbe poszczeglnych cyfr
//          "NIE" w przeciwnym wypadku


// zloz. czas = O(log10(m*n))
// zloz. pam = O(1)
int main(void) 
{
    int n, m, k = 0, cyfra;
    printf("Podaj dwie liczby naturalne do sprawdzenia\n");
    scanf("%d%d", &n, &m);
    int liczby1[10] = {0};
    int liczby2[10] = {0};

    while (n > 0)
    {
        cyfra = n % 10;
        liczby1[cyfra]++;
        n = n / 10;
    }

    while (m > 0)
    {
        cyfra = m % 10;
        liczby2[cyfra]++;
        m = m / 10;
    }

    for (int i = 0; i < 9; i++)
    {
        if (liczby1[i] != liczby2[i])
        {
            printf("Liczby nie są podobne\n");
            return 0;
        }
    }

    printf("Liczby sa podobne\n");
    return 0;
}