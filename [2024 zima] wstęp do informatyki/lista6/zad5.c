#include <stdio.h>
#include <math.h>

void sito_eratostenesa(int n, int s[]) // O(n*log2(log2(n)))
{
    // inicjalizacja: wszystkie liczby od 2 do n są "pierwsze"
    for (int i = 0; i <= n; i++) 
    {
        s[i] = 1;
    }
    s[0] = s[1] = 0;  // 0 i 1 nie są liczbami pierwszymi

    // algorytm sita eratostenesa
    for (int i = 2; i*i <= n; i++) 
    {
        // jeśli i jest potencjalnie pierwsza
        if (s[i] == 1) 
        {  
            // oznacz wszystkie wielokrotności i jako nie-prime (0)
            for (int j = i * i; j <= n; j += i) 
            {
                s[j] = 0;
            }
        }
    }
}

