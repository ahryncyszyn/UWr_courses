#include <stdio.h>

int main(void)
{
    // wczytanie zmiennych 
    int n, m, d;
    scanf("%d", &n); // liczba grzadek
    scanf("%d", &m); // liczba kaktusow w grzadce
    scanf("%d", &d); // liczba dni

    // wczytanie grzadek kaktusow
    long long kaktusy[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%lld", &kaktusy[i][j]);
        }
    }
    
    // obliczenie poczatkowej wysokosci
    long long curr_height = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            curr_height += kaktusy[i][j];
        }
    }
    
    long long max_height = curr_height;
    long long new_height;
    int dzien = 0;

    // symulacja wzrostu kaktusow
    // w najgorszym wypadku (h = 38000000), 176 dni zajmuje 
    // kaktusowi dojscie do powtarzalnej sekwencji (4, 1, 2)
    // więc symulujemy 176 * n dni zeby zapewnic ze kazda grzadka bedzie nawozona min 176 razy
    int limit = (d < (176 * n)) ? d : (176 * n);
    for (; dzien < limit; dzien++)
    {
        // uzywamy modulo do wyznaczenia zakresu nawozonych grzadek
        int max_grzadki = dzien % n + 1;
        for (int grzadka = 0; grzadka < max_grzadki; grzadka++)
        {
            for (int i = 0; i < m; i++)
            {
                if (kaktusy[grzadka][i] % 2 == 0) 
                {
                    new_height = kaktusy[grzadka][i] / 2;
                } else
                {
                    new_height = kaktusy[grzadka][i] * 3 + 1;
                }
                curr_height += new_height - kaktusy[grzadka][i];
                kaktusy[grzadka][i] = new_height;
            }
        }
        // zapisywanie maksymalnej wysokosci
        if (curr_height > max_height) 
            max_height = curr_height;
    }

    // dla reszty dni obliczamy wysokosc z sekwencji (4, 1, 2)
    // mozliwosci jest tylko 3 * n 
    limit = ((d - dzien) > (3 * n)) ? (3 * n) : (d - dzien);
    for (; dzien < limit; dzien++)
    {
        // uzywamy modulo do wyznaczenia zakresu nawozonych grzadek
        int max_grzadki = dzien % n + 1;
        for (int grzadka = 0; grzadka < max_grzadki; grzadka++)
        {
            for (int i = 0; i < m; i++)
            {
                if (kaktusy[grzadka][i] == 4) 
                    new_height = 1;
                else if (kaktusy[grzadka][i] == 1)
                    new_height = 2;
                else
                    new_height = 4;
                curr_height += new_height - kaktusy[grzadka][i];
                kaktusy[grzadka][i] = new_height;
            }
        }
        // zapisywanie maksymalnej wysokosci
        if (curr_height > max_height) 
            max_height = curr_height;
    }

    printf("%lld", max_height);
    return 0;
}