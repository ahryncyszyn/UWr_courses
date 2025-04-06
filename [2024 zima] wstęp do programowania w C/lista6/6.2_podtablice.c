// Aleksandra Hryncyszyn, 353636
// zad 2, lista 6

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ZAKRES 1001

void wczytanieDoTablicy(int rozmiar, int tab[]);
int obliczHash(int prefixy[], int start, int end);

int main(void)
{
    // wczytanie tablic S i T
    int rozmiar = -1;
    while (rozmiar < 1)
    {
        printf("Podaj rozmiar tablic (dodatnia liczba naturalna)\n");
        scanf("%d", &rozmiar);
    }
    printf("Podaj po %d elementow dla obu tablic\n", rozmiar);
    int S[rozmiar], T[rozmiar];
    wczytanieDoTablicy(rozmiar, S);
    wczytanieDoTablicy(rozmiar, T);

    // stworzenie pomocniczej tablicy z losowymi liczbami
    srand(time(NULL));
    int r[ZAKRES];
    for (int i = 0; i < ZAKRES; i++)
        r[i] = rand();

    // tablica prefixowa P dla zbioru S
    // P[0] = r[S[0]], P[1] = r[S[0]] ^ r[S[1]], ...
    int P[rozmiar];
    P[0] = r[S[0]];
    for (int i = 1; i < rozmiar; i++)
    {
        P[i] = P[i-1] ^ r[S[i]];
    }

    // tablica prefixowa Q dla zbioru T
    int Q[rozmiar];
    Q[0] = r[T[0]];
    for (int i = 1; i < rozmiar; i++)
    {
        Q[i] = Q[i-1] ^ r[T[i]];
    }

    // wczytanie liczby zapytan
    int zapytania = -1;
    while (zapytania < 0)
    {
        printf("Podaj liczbe zapytan (dodatnia liczba naturalna):\n");
        scanf("%d", &zapytania);
    }
    
    // sprawdzanie zapytan:
    // czy S[i...i+k] i T[j...j+k] maja te same liczby
    int i, j, k, hashS, hashT;
    for (int z = 0; z < zapytania; z++)
    {
        scanf("%d%d%d", &i, &j, &k);
        hashS = obliczHash(P, i, i + k);
        hashT = obliczHash(Q, j, j + k);

        if (hashS == hashT) printf("TAK\n");
        else printf("NIE\n");
    }
}

void wczytanieDoTablicy(int rozmiar, int tab[])
{   
    for (int i = 0; i < rozmiar; i++)
    {
        scanf("%d", &tab[i]);
        if (tab[i] > 1000 || tab[i] < 1)
        {
            printf("Dozwolone liczby z zakresu [1, 1000]\n");
            exit(1);
        }
    }
}

int obliczHash(int prefixy[], int start, int end)
{
    if (start == 0) return prefixy[end];
    return prefixy[end] ^ prefixy[start - 1];
}