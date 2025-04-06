#include <stdio.h>

int main(void){
    
    // wczytanie liczby elementow ciagu, n
    int n = 0;
    while(n <= 0)
    {
        scanf("%d", &n);
    }

    // wczytanie ciagu zaleznosci do tablicy
    int zaleznosci[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &zaleznosci[i]);
    } 

    // inicjalizacja ciagu na same 1
    int ciag[n];
    for (int i = 0; i < n; i++)
        ciag[i] = 1;

    // dostosowanie warunkow "1"
    for (int i = 0; i < n - 1; i++)
    {
        if (zaleznosci[i] == 1)
            ciag[i + 1] = ciag[i] + 1;
    }

    // dostosowanie warunkow "-1"
    for (int i = n - 2; i >= 0; i--)
    {
        if (zaleznosci[i] == -1)
        {
            if (ciag[i] <= ciag[i + 1])
                ciag[i] = ciag[i + 1] + 1;
        }
    }

    // wypisanie wyniku
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", ciag[i]);
    }
    return 0;
}
