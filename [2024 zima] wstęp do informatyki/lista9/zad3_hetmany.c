#include <stdio.h>

int poprawne(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] - i == a[j] - j || a[i] + i == a[j] + j || a[i] == a[j]) return 0;
        }
    }
    return 1;
}

// sprawdza wszystkie mozliwosci ustawienia hetmanow: n^n
// backtracking sprawdza mniej niz n^n mozliwosci, bo rekurencja jest odcinana w momencie wykrycia konfliktu
int hetmany (int n, int k, int a[]) 
{
    if (k == n) return poprawne (a, n);
    for (int i = 0; i < n ; i ++) 
    {
        a[k] = i;
        if (hetmany(n, k + 1, a)) return 1;
    }
    return 0;
}

int main()
{
    int n = 5;
    int a[] = {-1, -1, -1, -1, -1};
    printf("%d\n", hetmany(n, 0, a));
    return 0;
}