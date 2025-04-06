
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem* osoba;
typedef unsigned int uint;
#define MAX_LEN 2007
#define MAX_NAME_LEN 1001

struct elem 
{
    char* imie;
    uint wiek;
    struct elem* next;
};

/*
+ <imię> <wiek> - do kolejki przychodzi osoba o imieniu <imię> i wieku <wiek>,
- <imię> - osoba o imieniu <imię> opuszcza kolejkę,
O X - X osób opuszcza klub,
F <imię> <wiek> <imię_kolegi> - do kolejki przychodzi osoba o imieniu <imię> i wieku <wiek>, która koleguje się z <imię_kolegi>, więc osoba o imieniu <imię_kolegi> wpuści ją przed siebie (załóż, że kolega zawsze jest w kolejce),
Z - klub się zamyka.
*/

osoba stworz_osobe(char imie[], uint wiek);
void usun_osobe(osoba* kolejka, char imie[]);
void wpusc_X_osob(osoba* kolejka, uint* liczba_osob);
void wpusc_kolege(osoba* kolejka, char imie[], uint wiek, char imie_kolegi[]);


int main()
{
    // stworzenie pustej kolejki
    osoba kolejka = NULL;

    // zmienne pomocnicze
    char polecenie[MAX_LEN];
    char imie[MAX_NAME_LEN];
    char imie_kolegi[MAX_NAME_LEN];
    uint wiek, do_wpuszczenia = 0;

    // wczytywanie polecen az do "Z", czyli zamkniecia
    while (1)
    {
        fgets(polecenie, MAX_LEN, stdin);
        
        // dodawanie osoby do kolejki
        if (strncmp(polecenie, "+", 1) == 0)
        {
            sscanf(polecenie, "+ %s %u", imie, &wiek);

            // stworzenie nowej osoby
            osoba nowa_osoba = stworz_osobe(imie, wiek);
            printf("Stworzona nowa osobe %s\n", nowa_osoba -> imie);

            // dodanie nowego osoby na koniec kolejki
            if (kolejka == NULL) kolejka = nowa_osoba;
            else 
            {
                osoba curr = kolejka;
                while (curr -> next != NULL) curr = curr -> next;
                curr -> next = nowa_osoba;
            }
        }
        // wypisywanie zawartosci kolejki
        if (strncmp(polecenie, "W", 1) == 0)
        {
            if (kolejka == NULL) printf("Kolejka jest pusta\n");
            else 
            {
                osoba curr = kolejka;
                while (curr != NULL)
                {
                    printf("%s\n", curr -> imie);
                    curr = curr -> next;
                }
            }
        }
        // usuwanie osoby z kolejki
        else if (strncmp(polecenie, "-", 1) == 0)
        {
            sscanf(polecenie, "- %s", imie);
            usun_osobe(&kolejka, imie);
        }
        // wpuszczanie osob do klubu
        else if (strncmp(polecenie, "O", 1) == 0)
        {
            sscanf(polecenie, "O %u", &do_wpuszczenia);
            wpusc_X_osob(&kolejka, &do_wpuszczenia);
        }
        else if (strncmp(polecenie, "F", 1) == 0)
        {
            sscanf(polecenie, "F %s %u %s", imie, &wiek, imie_kolegi);
            wpusc_kolege(&kolejka, imie, wiek, imie_kolegi);
        }
        else if (strncmp(polecenie, "Z", 1) == 0)
        {
            return 1;
        }

        // wpuszczenia dodatkowych osob jezeli jest jeszcze miejsce
        if (do_wpuszczenia > 0) 
        {
            wpusc_X_osob(&kolejka, &do_wpuszczenia);
        }
    }

    return 0;
}

osoba stworz_osobe(char imie[], unsigned int wiek)
{
    osoba nowa_osoba = malloc(sizeof(struct elem));
    if (nowa_osoba == NULL) return NULL;

    nowa_osoba -> imie = malloc(sizeof(char) * (strlen(imie) + 1));
    if (nowa_osoba -> imie == NULL)
    {
        free(nowa_osoba);
        return NULL;
    }

    strcpy(nowa_osoba -> imie, imie);
    nowa_osoba -> wiek = wiek;
    nowa_osoba -> next = NULL;
    return nowa_osoba;
}

void usun_osobe(osoba* kolejka, char imie[])
{
    if (*kolejka == NULL) return;
    osoba to_delete;
    if (strcmp((*kolejka) -> imie, imie) == 0)
    {
        to_delete = (*kolejka);
        (*kolejka) = (*kolejka) -> next;
        free(to_delete -> imie);
        free(to_delete);
        return;
    } 

    osoba curr = *kolejka;
    while (curr -> next != NULL && strcmp(curr -> next -> imie, imie) != 0)
    {
        curr = curr -> next;
    }
    if (curr -> next != NULL)
    {
        to_delete = curr -> next;
        curr -> next = curr -> next -> next;
        free(to_delete -> imie);
        free(to_delete);
    }
}
       
void wpusc_X_osob(osoba* kolejka, uint* do_wpuszczenia)
{
    while ((*do_wpuszczenia) > 0 && (*kolejka) != NULL)
    {
        if ((*kolejka) -> wiek >= 18)
        {
            printf("wpuszczono %s\n", (*kolejka) -> imie);
            (*do_wpuszczenia)--;
        }
        osoba to_delete = (*kolejka);
        (*kolejka) = (*kolejka) -> next;
        free(to_delete -> imie);
        free(to_delete);
    }
}
  
void wpusc_kolege(osoba* kolejka, char imie[], uint wiek, char imie_kolegi[])
{
    osoba nowa_osoba = stworz_osobe(imie, wiek);
    if (nowa_osoba == NULL) return;

    // kolega jest na poczatku kolejki
    if (strcmp((*kolejka) -> imie, imie_kolegi) == 0)
    {
        nowa_osoba -> next = (*kolejka);
        (*kolejka) = nowa_osoba;
        return;
    }

    osoba curr = (*kolejka);
    osoba prev = NULL;
    while (curr != NULL && strcmp(curr -> imie, imie_kolegi) != 0)
    {
        prev = curr;
        curr = curr -> next;
    }
    if (curr != NULL)
    {
        prev -> next = nowa_osoba;
        nowa_osoba -> next = curr;
    }
    else
    {
        free(nowa_osoba -> imie);
        free(nowa_osoba);
    }
}