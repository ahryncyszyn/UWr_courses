#include <stdio.h>

// zloz. czas = O(1)
// zloz. pam = O(1)
int funkcjaA(int n) 
{
    if (n % 2 == 0) return n;
    return (-n);
}

// zloz. czas = O(n)
// zloz. pam = O(1)
double funkcjaB(int n)
{
    double res = 0.0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            res -= 1.0 / i;
        else  
            res += 1.0 / i;
    }
    return res;
}

// zloz. czas = O(n)
// zloz. pam = O(1)
int funkcjaC(int n, int x)
{
    int res = 0;
    int x1 = x;
    for (int i = 1; i <= n; i++)
    {
        res += i * x;
        x = x * x1;
    }
    return res;
}

int main()
{
    int n, x;
    printf("Podaj liczbe n oraz x\n");
    scanf("%d%d", &n, &x);

    printf("Funkcja a): %d\n", funkcjaA(n));
    printf("Funkcja b): %f\n", funkcjaB(n));
    printf("Funkcja c): %d\n", funkcjaC(n, x));

}