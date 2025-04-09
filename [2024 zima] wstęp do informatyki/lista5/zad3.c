#include <stdio.h>

// Wejscie: n, m - liczby naturalne
// Wyjscie: NWD(n, m)
// nwd(2n, 2m) = 2 · nwd(n, m)
// nwd(2n, m) = nwd(n, m) dla nieparzystej liczby m > 0

int gcdR(int n, int m)
{
    int oddcnt;
    if (!m) return n;
    if (n < m) return gcdR(m, n);

    oddcnt = n % 2 + m % 2;
    if (oddcnt == 2) return gcdR(n - m,  m);
    if (!oddcnt) return 2 * gcdR (n/2, m/2);
    if (n % 2 == 0) return gcdR(n/2, m);
    else return gcdR(n, m/2);
}

int gcdI(int n, int m)
{
    int multipl = 1;
    while (m != 0)
    {
        if (n < m)
        {   
            int temp = n;
            n = m;
            m = temp;
        }

        int oddcnt = n % 2 + m % 2;
        if (oddcnt == 2) n -= m;
        else if (oddcnt == 0) 
        {
            multipl *= 2;
            n /= 2;
            m /= 2;
        }
        else if (n % 2 == 0) n /= 2;
        else m /= 2;
    }
    return multipl * n;
}

int main(void)
{
    int n = 33, m = 12;
    int wyn1 = gcdR(n, m);
    int wyn2 = gcdI(n, m);
    printf("wersja R: %d, wersja I: %d\n", wyn1, wyn2);
    return 0;
}
