// Aleksandra Hryncyszyn, 353636
// lista 3, zadanie 2

#include <stdio.h>
#include <string.h>

int czyPoprawneWejscie(char *kwota);
int zliczenieGroszy(char *kwota);
int rozmienienieKwoty(int grosze);

int main(int argc, char *argv[])
{
    // zwraca blad jezeli zostalo podane za duzo argumentow
    if (argc != 2) {
        printf("BLAD\n");
        return 1;
    }

    // weryfikuje czy argument jest poprawny
    if (!czyPoprawneWejscie(argv[1])) {
        printf("BLAD\n");
        return 1;
    }

    // zlicza grosze dla poprawnosci obliczen
    int grosze = zliczenieGroszy(argv[1]);

    // rozmienia na najmniejsza liczbe monet
    rozmienienieKwoty(grosze);

    return 0;
}

int czyPoprawneWejscie(char *kwota)
{
    int dlugosc = strlen(kwota);
    int kropki = 0, przecinki = 0;
    int poz_sep = -1;

    if (dlugosc == 0) return 0;

    // zliczenie kropek i przecinkow
    for (int i = 0; i < dlugosc; i++)
    {
        if (kwota[i] == '.')
        {
            poz_sep = i;
            kropki++;
        }
        else if (kwota[i] == ',')
        {
            poz_sep = i;
            przecinki++;
        }

        // odrzucenie jezeli znak nie jest '.' ',' lub cyfra
        else if (kwota[i] < '0' || kwota[i] > '9') return 0;
    }

    if (kropki + przecinki > 1) return 0;

    // sprawdzenie czy sa max dwie cyfry po separatorze
    if ((dlugosc - poz_sep - 1) > 2) return 0; 

    // w przeciwnym wypadku kwota jest poprawna
    return 1;
}

int zliczenieGroszy(char *kwota)
{
    int dlugosc = strlen(kwota);
    int poz_separatora = -1;
    int grosze = 0;
    int potega = 1;

    // znalezienie pozycji kropki/przecinka
    for (int i = 0; i < dlugosc; i++)
    {
        if (kwota[i] == '.' || kwota[i] == ',')
        {
            poz_separatora = i;
            break;
        }
    }

    // jezeli nie znaleziono separatora
    // traktujemy cala kwote jako czesc calkowita
    if (poz_separatora < 0)
    {
        for (int i = dlugosc - 1; i >= 0; i--)
        {   
            grosze += (kwota[i] - '0') * potega;
            potega *= 10;
        }
        return grosze * 100;
    }
    
    // dla liczby z separatorem najpierw 
    // zliczamy czesc calkowita
    for (int i = poz_separatora - 1; i >= 0; i--)
    {
        grosze += (kwota[i] - '0') * potega;
        potega *= 10;
    }
    grosze *= 100;

    // dodajemy czesc po separatorze
    potega = 10;
    for (int i = poz_separatora + 1; i < dlugosc; i++)
    {
        grosze += (kwota[i] - '0') * potega;
        potega /= 10;
    }
    return grosze;
}

int rozmienienieKwoty(int grosze)
{
    // przechowuje mozliwe monety w groszach
    int monety[] = {500, 200, 100, 50, 20, 10 , 5, 2, 1};
    // przechowuje liczbe poszczegolnych monet
    int liczby_monet[9] = {0};

    // zliczenie liczb poszczegolnych monet
    for (int i = 0; i < 9; i++)
    {
        liczby_monet[i] = grosze / monety[i];
        grosze %= monety[i];
    }

    // wypisanie wyniku
    for (int i = 0; i < 9; i++)
    {
        if (liczby_monet[i] > 0)
        {
            // wersja dla zlotowek
            if (monety[i] >= 100)
                printf("%dx%dzl\n", liczby_monet[i], monety[i]/100);

            // wersja dla groszy
            else printf("%dx%dgr\n", liczby_monet[i], monety[i]);
        }
    }

    return 1;
}