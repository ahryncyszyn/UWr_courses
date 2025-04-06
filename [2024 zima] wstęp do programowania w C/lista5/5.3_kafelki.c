#include <stdio.h>
#include <limits.h>

// wejscie: n, m (n < 1000) - wymiary planszy
//          n x m liczb naturalnych < 1000 - wielkosci kar na danym kafelku
// wyjscie: minimalna kara jaka nalezy zaplacic za przejscie na prawa strone
//          (kafelek po lewej mozna wybrac)

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(void)
{
    // wczytanie wymiarow planszy
    int n, m;
    scanf("%d%d", &n, &m);

    // wczytanie planszy
    int kafelki[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &kafelki[i][j]);
        }
    }

    // obliczanie ile min kary trzeba zaplacic 
    // zeby dojsc do danego kafelka
    int min_kara;
    for (int j = 1; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            min_kara = kafelki[i][j-1];
            if (i > 0) min_kara = MIN(min_kara, kafelki[i-1][j-1]);
            if (i < n - 1) min_kara = MIN(min_kara, kafelki[i+1][j-1]);
            
            kafelki[i][j] += min_kara;
        }
    }

    // szukanie min sumy w ostatniej kolumnie
    int min_suma_kar = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (kafelki[i][m-1] < min_suma_kar) min_suma_kar = kafelki[i][m-1];
    }
    printf("%d", min_suma_kar);
}