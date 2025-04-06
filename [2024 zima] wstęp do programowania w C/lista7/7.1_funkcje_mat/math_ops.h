
#include <limits.h>
#include <stdio.h>

// oblicza n! dla liczby naturalnej n
// w przypadku blednego wejscia lub silni
// przekraczajacej zakres inta, zwraca -1
int factorial(int n);

// przjmuje podstawe bedaca liczba rzeczywista
// i wykladnik bedacy liczba calkowita
// oblicza potege base ** exponent
double power(double base, int exponent);

// sprawdza czy number jest liczba pierwsza
// zwraca 1 jezeli jest lub 0 jezeli nie jest
int is_prime(int number);
