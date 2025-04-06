// Aleksandra Hryncyszyn, 353636
// zad 1, lista 5
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <ctype.h>
#include <string.h>

#define AFTER_BLANK 1
#define NOT_AFTER_BLANK 0

void max_min_avg(double tab[], int len, double* max, double* min, double* avg)
{
    *max = DBL_MIN; *min = DBL_MAX; *avg = 0;
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (tab[i] > *max) *max = tab[i];
        if (tab[i] < *min) *min = tab[i];
        sum += tab[i];
    }
    *avg = sum / len;
}

char* najwczesniejsze_wyst(char napis[], char znak)
{
    char* p = napis;
    while (*p != '\0')
    {
        if (*p == znak) return p;
        p++;
    }
    return NULL;
}

char* najpozniejsze_wyst(char napis[], char znak)
{
    char* p = NULL;
    while (*napis != '\0')
    {
        if (*napis == znak) p = napis;
        napis++;
    }
    return p;
}

void naWielkie(char napis[])
{
    while (*napis != '\0')
    {
        *napis = toupper(*napis);
        napis++;
    }
}

void naMale(char napis[])
{
    while (*napis != '\0')
    {
        *napis = tolower(*napis);
        napis++;
    }
}

void naTitlecase(char napis[])
{
    int pozycja = AFTER_BLANK;
    while (*napis != '\0')
    {
        if (pozycja == AFTER_BLANK)
        {
           *napis = toupper(*napis);
           pozycja = NOT_AFTER_BLANK;
        }
        else *napis = tolower(*napis);

        if (isblank(*napis)) pozycja = AFTER_BLANK;
        napis++;
    }
}

void naOdwrocony(char napis[])
{
    char* start = napis;
    char* end = napis + strlen(napis) - 1;
    char temp;
    while (start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main(void)
{
    double tab[] = {1, 2, 3};
    int len = 3;
    double max = DBL_MIN, min = DBL_MAX, avg = 0;
    max_min_avg(tab, len, &max, &min, &avg);
    printf("Wynik funkcji: max = %.2lf, min = %.2lf, avg = %.2lf\n\n", max, min, avg);

    char napis[] = "abcd efghi";
    char znak = 'f';
    printf("Pointer do najwczesniejszego wystapienia znaku to: %p\n", najwczesniejsze_wyst(napis, znak));
    printf("Pointer do najpozniejszego wystapienia znaku to: %p\n\n", najpozniejsze_wyst(napis, znak));

    naWielkie(napis);
    printf("Napis z literami zamienionymi na wielkie: %s\n", napis);
    naMale(napis);
    printf("Napis z literami zamienionymi na male: %s\n", napis);
    naTitlecase(napis);
    printf("Napis z literami zamienionymi na titlecase: %s\n", napis);
    naOdwrocony(napis);
    printf("Napis po odwroceniu: %s\n", napis);

    return 0;
}
