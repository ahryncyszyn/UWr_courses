#include <stdio.h>

// Wejście: n, m - liczby naturalne
// Wyjście: najmniejsza liczba naturalna k, t.z. n^k >= m

int pot(int n, int m)
{ 
    int rez = 1;
    while (m > 0) 
    {
        if (m % 2) rez = rez * n; 
        m = m / 2;
        n = n * n;
    }
    return rez; 
}

int min_k(int n, int m) {
    int k = 1;
    int potega = n;

    // Wyszukiwanie binarne w zakresie [k/2, k]
    int low = k / 2;
    int high = k;

    while (low < high) 
    {
        int mid = (low + high) / 2;
        if (pot(n, mid) >= m) 
        {
            high = mid;
        } else 
        {
            low = mid + 1;
        }
    }

    return low;  // lub high, ponieważ low == high
}



int min_k_wol(int n, int m) {
    int k = 0;
    int result = 1;

    // Dopóki n^k jest mniejsze niż m, zwiększaj k i wynik przez mnożenie n
    while (result < m) {
        result *= n;
        k++;
    }

    return k;
}


int main(void)
{
    int n = 5, m = 3;
    printf("wynik to: %d\n", pot(n, m));
    return 0;
}
