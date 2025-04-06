#include <stdio.h>
#include <limits.h>

int factorial(int n)
{
    if (n < 0)
    {
        printf("Argument funkcji nie moze byc ujemny\n");
        return -1;
    }

    if (n == 0) return 1;

    long long res = 1;
    for (int  i = 1; i <= n; i++)
    {
        res *= i;
        if (res > INT_MAX)
        {
            printf("Wynik %d! nie miesci sie w zakresie integera\n", n);
            return -1;
        }
    }
    return (int) res;
}

double power(double base, int exponent)
{
    double res = 1.0;
    if (exponent == 0) return 1.0;
    if (exponent > 0)
    {
        for (int i = 1; i <= exponent; i++)
        {
            res *= base;
        }
    }
    if (exponent < 0)
    {
        for (int i = 1; i <= exponent; i++)
        {
            res /= base;
        }
    }
    return res;
}

int is_prime(int number)
{
    if (number < 2) return 0;
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0) return 0;
    }
    return 1;
}
