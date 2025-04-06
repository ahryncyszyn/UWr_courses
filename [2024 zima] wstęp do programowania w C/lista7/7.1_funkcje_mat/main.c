// Aleksandra Hryncyszyn, 353636

#include "math_ops.h"
#include "number_utils.h"

int main(void)
{
    int n; double m;
    printf("Podaj liczbe calkowita\n");
    scanf("%d", &n);
    printf("Podaj liczbe niecalkowita\n");
    scanf("%lf", &m);

    printf("Wynik operacji %d! to: %d\n", n, factorial(n));

    printf("Wynik %.2lf do potegi %d to: %.2lf\n", m, n, power(m, n));

    if (is_prime(n) == 1) printf("Liczba %d jest liczba pierwsza\n", n);
    else printf("Liczba %d nie jest liczba pierwsza\n", n);

    printf("Liczba cyfr liczby %d to: %d\n", n, count_digits(n));

    printf("Liczba bedaca odwroceniem liczby %d to: %d\n", n, reverse_number(n));

    printf("Suma cyfr liczby %d to: %d\n", n, digit_sum(n));

    return 0;
}
