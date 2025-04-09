#include <stdio.h>
// Wejście: n – dodatnia liczba całkowita, a1, . . . , an – liczby naturalne
// Wyjście: nwd(a1, . . . , an) = max{b : b|ai dla każdego i ∈ {1, . . . , n} }.

// zloz. czas = O(log2(n+m))
int nwd(int n, int m)
{
    int k;
    while (m != 0) 
    {
        k = n % m; 
        n = m;
        m = k;
    }
}

int main(void) // O(n*log2(n+m))
{
    // wczytanie zmiennej n
    int n;
    printf("Podaj n, czyli liczbę liczb w ciągu\n");
    scanf("%d", &n);

    // wczytanie zbioru liczb
    int a[n];
    for (int i = 0; i < n; i++)
    {
        printf("Podaj liczbę\n");
        scanf("%d", &a[i]);
    }

    // przypadek dla jednej liczby osobno
    if (n == 1) return a[0];

    // obliczenie nwd zbioru
    // NWD(a, b, c) = NWD(a, (NWD(b, c)))
    // NWD(a, b, c) = max{p: p|a ^ p|b ^ p|c}
    // NWD(a, (NWD(b, c))) = max{p: p|a ^ p|max{ q: q|b ^ q|c}}
    //                     = max{p: p|a ^ p|b ^ p|c}
    // podzielnosc jest przechodnia - (p|q ^ q|b) ==> p|b
    // przyklad: (4, 12, 24) = (2*2, 2*2*3, 2*2*2*3) = (2*2, 2*2*2*3) = (2*2)
    int nwd_zbioru = nwd(a[0], a[1]);
    for (int i = 2; i < n; i++)
    {
        nwd_zbioru = nwd(nwd_zbioru, a[i]);
        if (nwd_zbioru == 1) break;
    }
    printf("Najwiekszy wspolny dzielnik liczb w ciagu to: %d\n", nwd_zbioru);

}