// Aleksandra Hryncyszyn, 353636
// zad 1, lista 6

#include <stdio.h>

int main(void)
{
     // wczytanie zmiennych
     int k = -1, n = -1;
     while (k < 0 || n < 0 || n > 30)
     {
        printf("Podaj dwie liczby: k i n (n<=30):\n");
        scanf("%d%d", &k, &n);
     }

     // wczytanie zbioru liczb
     int wagi[n];
     printf("Podaj %d wag elementow\n", n);

     for (int i = 0; i < n; i++)
     {
        int liczba = -1;
        while (liczba < 0)
        {
            scanf("%d", &liczba);
        }
        wagi[i] = liczba;
     }

    // sprawdzanie ktore podzbiory spelniaja warunek sum() <= k
     unsigned int liczba_podzbiorow = 1 << n; // 2^n
     int licznik = 0;
     for (unsigned int maska = 0; maska < liczba_podzbiorow; maska++)
     {
        int suma_podzbioru = 0;
        // sprawdzanie kazdego indexu
        for (int index = 0; index < n; index++)
        {
            // sprawdzanie czy index i jest 1 w masce
            if (maska & (1U << index))
            {
                suma_podzbioru += wagi[index];
            }
        }
        if (suma_podzbioru <= k) licznik++;

     }

     printf("Liczba podzbiorow z sumaryczna waga mniejsza od %d: %d\n", k, licznik);
     return 0;
}
