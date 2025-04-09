#include <stdio.h>
// w = a[0]⋅2^k + a[1]⋅2^k−1 + ⋯ + a[k]⋅2^0


int value(int a[], int k) 
{
    int w = 0, i;
    for (i = 0; i <= k; i++) 
    {
        w = w * 2 + a[i];
    }
    return w;
}

int main(void)
{
    int a[] = {1, 0, 0, 0, 0};
    printf("Wynik to %d", value(a, 4));
}
