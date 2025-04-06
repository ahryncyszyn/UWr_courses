// Aleksandra Hryncyszyn, 353636
// zad 1, lista 6

#include <stdio.h>
#include <string.h>

int main(void)
{
    // wczytanie ciagow zerojedynkowych
    char wzorzec[61], tekst[61];
    printf("Podaj dwa ciągi zerojedynkowe w osobnych wierszach:\n");
    scanf("%s", wzorzec); 
    scanf("\n");

    // wczytanie drugiego ciagu tylko na dlugosc wzorca
    int dl_wzorca = strlen(wzorzec);
    int i = 0; char c;
    while ((c = getchar()) != '\n' && c != EOF && i < dl_wzorca)
    {
        tekst[i] = c;
        i++;
    }
    tekst[i] = '\0';

    // zamienienie wzorca i tekstu na dziesietne liczby calkowite
    unsigned long long wzorzec10 = 0;
    unsigned long long tekst10 = 0;
    for (int i = 0; i < dl_wzorca; i++)
    {
        //                 * 2      konwertuje z char na int
        wzorzec10 = (wzorzec10 << 1) | (wzorzec[i] - '0');
        tekst10 = (tekst10 << 1) | (tekst[i] - '0');
    }

    // szukanie wzorca w tekscie
    int index = 0;
    while (c != '\n' && c != EOF)
    {
        // ^ = xor daje 0 kiedy wartosci sa takie same
        if ((wzorzec10 ^ tekst10) == 0) printf("%d ", index);

        // wczytanie nowego bitu ze sprawdzanego tesktu:
        //                               'zeruje' wszystkie bity poza dlugoscia wzorca
        //         dodaje bit z prawej           (inaczej zostaja po << po lewej)
        tekst10 = ((tekst10 << 1) | (c - '0')) & ((1ULL << dl_wzorca) - 1);
        c = getchar(); index++;
    }
    // sprawdzenie ostatniej pozycji (petla sie juz nie wykona bo kolejny c to '/n')
    if ((wzorzec10 ^ tekst10) == 0) printf("%d ", index);
    return 0;

}
