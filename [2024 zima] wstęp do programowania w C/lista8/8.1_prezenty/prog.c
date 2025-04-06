
// Aleksandra Hryncyszyn, 353636
// zad1, lista 8

#include "beneficjent.h"

int main(void)
{

    struct Osoba* os0 = nowa_osoba("Aleksandra", 22);
    struct Osoba* os2 = nowa_osoba("Witek", 22);
    ustaw_statystyki(os0, 100, 0);
    ustaw_statystyki(os2, 0, 100);
    wypisz_info(os0);
    wypisz_info(os2);

    usun_osobe(os0);
    if(os0 == NULL)
    {
        printf("Osoba1 zostala usunieta!\n");
    }
    else printf("Nie powiodlo sie usuwanie osoby\n");
    struct Osoba* os1 = nowa_osoba("Aleksandra", 22);

    printf("Stare imie osoby2 to %s\n", os2->imie);
    zmien_imie(os2, "Witus");
    printf("Nowe imie osoby2 to %s\n", os2->imie);

    printf("%s ma %hhu lat\n", os2->imie, os2->wiek);
    zmien_wiek(os2, 50);
    printf("Po zmianie %s ma %hhu lat\n", os2->imie, os2->wiek);

    wypisz_info(os1);
    dodaj_zasluge(os1);
    wypisz_info(os1);

    wypisz_info(os2);
    dodaj_szelmostwo(os2);
    wypisz_info(os2);

    printf("Czy %s dostanie prezent? %d \n", os1->imie, czy_dostanie_prezent(os1));
    wypisz_info(os1);
    wypisz_info(os2);
    printf("Wczesniejszy do kolejki po prezent jest %d\n", komparator(os1, os2));

    return 0;
}
