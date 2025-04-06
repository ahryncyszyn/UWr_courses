// Aleksandra Hryncyszyn, 353636
// lista 4, zadanie 2
// wejscie: n - dodatnia liczba calkowita, n < 40 000
// wyjscie: liczbę różnych rozwiązań równania: a + b + c = n
// a = liczba 1-pierwsza, b = liczba 5-pierwsza, c = liczba 7-pierwsza

#include <stdio.h>
#define MAX 40001

int liczba_czynnikow[MAX] = {}, pierwsze[MAX] = {}, pierwsze5[MAX] = {}, pierwsze7[MAX] = {};

void znajdzKpierwsze(int n);

int main(void)
{
    // wczytanie zmiennej n
    int n;
    scanf("%d", &n);

    // znalezienie liczb pierwszych, 5-pierwszych i 7-pierwszych
    znajdzKpierwsze(n);

    // znalezienie liczby rozwiazan rownania a + b + c = n
    int liczba_rozwiazan = 0;
    for (int a = 2; a < n; a++)
    {
        if (pierwsze[a] == 0) continue;

        for (int b = 2; b < n - a; b++)
        {
            if (pierwsze5[b] == 0) continue;

            int c = n - a - b;
            if (c > 0 && c < n && pierwsze7[c])
            {
                liczba_rozwiazan++;                
            }
        }
    }
    printf("%d\n", liczba_rozwiazan);

    return 0;
}

void znajdzKpierwsze(int n)
{
    // zliczamy liczbe czynnikow pierw. dla kazdej liczby
    // dzialanie podobne do sita erastotenesa
    for (int i = 2; i < n; i++)
    {
        // patrzymy tylko na liczby pierwsze
        if (liczba_czynnikow[i] == 0)
        {
            for (int wielokr = i; wielokr < n; wielokr += i)
            {
                int liczba = wielokr;
                // dany czynnik moze wystepowac czesciej niz raz
                while (liczba % i == 0)
                {
                    liczba_czynnikow[wielokr]++;
                    liczba /= i;
                }
            }
        }
    }

    // oznaczamy liczby k-pierwsze
    for (int i = 2; i < n; i++) 
    {
        if (liczba_czynnikow[i] == 1) pierwsze[i] = 1;    
        if (liczba_czynnikow[i] == 5) pierwsze5[i] = 1; 
        if (liczba_czynnikow[i] == 7) pierwsze7[i] = 1;
    }
}