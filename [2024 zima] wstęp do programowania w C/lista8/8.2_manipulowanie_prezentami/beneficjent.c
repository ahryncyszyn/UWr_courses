#include "beneficjent.h"

static unsigned akt_indeks = 0;

struct Osoba* nowa_osoba(char* imie, uint8_t wiek)
{
    struct Osoba* nowa = (struct Osoba*)malloc(sizeof(struct Osoba));
    if (nowa == NULL) return NULL;
    nowa->imie = malloc(sizeof(char) * strlen(imie));

    if (nowa->imie == NULL)
    {
        free(nowa);
        return NULL;
    }

    strcpy(nowa->imie, imie);
    nowa->wiek = wiek;
    nowa->zaslugi = 0;
    nowa->szelmostwa = 0;
    nowa->indeks = akt_indeks;
    akt_indeks++;

    return nowa;
}

void usun_osobe(struct Osoba* osoba)
{
    if (osoba == NULL) return;

    free(osoba->imie);
    free(osoba);
    return;
}

void zmien_imie(struct Osoba* osoba, char* imie)
{
    if (osoba == NULL) return;
    osoba->imie = realloc(osoba->imie, sizeof(char) * strlen(imie));
    strcpy(osoba->imie, imie);
    return;
}

void zmien_wiek(struct Osoba* osoba, uint8_t wiek)
{
    if (osoba == NULL) return;
    osoba->wiek = wiek;
}

void dodaj_zasluge(struct Osoba* osoba)
{
    if (osoba == NULL) return;
    osoba->zaslugi += 1;
}

void dodaj_szelmostwo(struct Osoba* osoba)
{
    if (osoba == NULL) return;
    osoba->szelmostwa += 1;
}

void ustaw_statystyki(struct Osoba* osoba, unsigned int zaslugi, unsigned int szelmostwa)
{
    if (osoba == NULL) return;
    osoba->zaslugi = zaslugi;
    osoba->szelmostwa = szelmostwa;
}

int czy_dostanie_prezent(struct Osoba* osoba)
{
    if (osoba->wiek < 4) return 1;
    if (osoba->zaslugi > osoba->szelmostwa) return 1;
    return 0;
}

void wypisz_info(struct Osoba* osoba)
{
    if (osoba == NULL) return;
    printf("Osoba o indeksie %u nazywa sie %s, ma %hhu lat, %u zaslug i %u szelmostw\n", osoba->indeks, osoba->imie, osoba->wiek, osoba->zaslugi, osoba->szelmostwa);
}

int komparator(const struct Osoba** os1, const struct Osoba** os2)
{
    long long roznica1 = (*os1)->zaslugi - (*os1)->szelmostwa;
    long long roznica2 = (*os2)->zaslugi - (*os2)->szelmostwa;

    if (roznica1 > roznica2) return -1;
    if (roznica2 > roznica1) return 1;
    if ((*os1)->wiek < (*os2)->wiek) return -1;
    if ((*os1)->wiek > (*os2)->wiek) return 1;
    return 0;
}
