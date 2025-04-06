// Aleksandra Hryncyszyn, 353636
// zad 2, lista 5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int compare_strings(char *str1, char *str2);
void ramkaPozioma(bool ramka, int n, char ramkaPoziom, char naroznik);

int main(int argc, char *argv[])
{
    // zweryfikowanie liczby argumentow
    if (argc > 4)
    {
        printf("za duzo argumentow wywolania\n");
        return 1;
    }

    // zdefiniowanie zmiennych do stylu wykresu
    bool ramka = false, wlasnyStyl = false;
    char slupek = '#', osX = '=', ramkaPion = '|', ramkaPoziom = '-', naroznik = '+';
    char* napis; int dl_napis;

    // dostosowanie warunkow z flag
    for(int i = 1; i < argc; i++)
    {
        if ((compare_strings(argv[i], "-b") && ramka) || (compare_strings(argv[i], "-m") && wlasnyStyl))
        {
            printf("Ta sama flaga nie powinna byc podana dwukrotnie\n");
            return 1;
        }
        else if (compare_strings(argv[i], "-b"))
        {
            ramka = true;
        }
        else if (compare_strings(argv[i], "-m"))
        {
            if (i == argc)
            {
                printf("Po fladze -m powinien byc podany napis\n");
                return 1;
            }
            wlasnyStyl = true;
            napis = argv[i+1];
            dl_napis = strlen(napis);
            i++; // zwiekszenie indeksu zeby nie interpretowal napisu jako flagi
        }
        else
        {
            printf("Niepoprawna flaga\n");
            return 1;
        }
        
    }
    if (wlasnyStyl && ramka && (dl_napis != 5)) 
    {
        printf("Dla wywołania z ramka napis powinien miec dlugosc 5\n");
        return 1;
    }
    if (wlasnyStyl && !ramka && (dl_napis != 2))
    {
        printf("Dla wywołania bez ramki napis powinine miec dlugosc 2\n");
        return 1;
    }

    // dostosowanie stylizacji wykresu do flag
    if (wlasnyStyl)
    {
        slupek = napis[0];
        osX = napis[1];
        if (ramka)
        {
            ramkaPion = napis[2];
            ramkaPoziom = napis[3];
            naroznik = napis[4];
        }
    }

    // wczytanie n
    int n; 
    scanf("%d", &n);

    // wczytanie tablicy z zaokraglonymi wartosciami funkcji
    int wartosci[n]; float num;
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &num);
        wartosci[i] = lroundf(num);
    }

    // wyznaczenie min i max wartosci
    int min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (wartosci[i] < min) min = wartosci[i];
        if (wartosci[i] > max) max = wartosci[i];
    }
    if (min > 0) min = 0;

    // drukowanie wykresu
    printf("\n");
    ramkaPozioma(ramka, n, ramkaPoziom, naroznik);
    for (int h = max; h >= min; h--)
    {
        for (int i = 0; i < n; i++)
        {
            if (ramka && (i == 0 || i == n-1))
            {
                if (h == 0) printf("%c", naroznik);
                else printf("%c", ramkaPion);
            }
            else if (h == 0) printf("%c", osX);
            else if (h > 0 && wartosci[i] >= h) printf("%c", slupek);
            else if (h < 0 && wartosci[i] <= h) printf("%c", slupek);
            else printf(" ");
        }
        printf("\n");
    }
    ramkaPozioma(ramka, n, ramkaPoziom, naroznik);
    return 0;
}

int compare_strings(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2) return 0;
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

void ramkaPozioma(bool ramka, int n, char ramkaPoziom, char naroznik)
{
    if (ramka)
    {
        printf("%c", naroznik);
        for (int i = 1; i < n - 1; i++) 
        {
            printf("%c", ramkaPoziom);
        }
        printf("%c", naroznik);
    }
    printf("\n");
}