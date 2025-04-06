#include <stdio.h>
#include <stdlib.h>

int ileDzielnikow(unsigned long long);

int main(int argc, char *argv[])
{
    // zweryfikowanie liczby argumentow wywolania
    if (argc != 2)
    {
        printf("Nieprawidłowa liczba argumentow wywołania\n");
        return 1;
    }

    // wczytanie argumentu N
    unsigned long long n = 0;
    char *endptr;
    n = strtoul(argv[1], &endptr, 10); 
    if (n == 0)
    {
        printf("Argument wywołania powininen być liczbą\n");
        return 1;
    }
    printf("n to: %llu\n", n);

    // sprawdzanie kolejnych liczb trojkatnych
    int index = 1;
    unsigned long long trojkatna = 1;
    int dzielniki = 1;
    while (dzielniki <= n)
    {
        index++;
        trojkatna += index;
        dzielniki = ileDzielnikow(trojkatna);
    }

    printf("Liczba trojkatna %llu ma index %d i %d dzielnikow\n", trojkatna, index, dzielniki);
    return 0;

}

int ileDzielnikow(unsigned long long trojkatna)
{
    int dzielniki = 0;
    for (int i = 1; i <= trojkatna; i++)
    {
        if (trojkatna % i == 0) dzielniki++;
    }
    return dzielniki;
}