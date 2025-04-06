// Aleksandra Hryncyszyn, 353636
// zad 2, lista 8

// sprawdzac poprawnosc indeksu

#include "beneficjent.h"

#define MAX_LEN 256
#define MAX_PERSON_COUNT 100

void wyswietl_instrukcje();
void bledne_dane();
int compare(const void* a, const void* b);

int main(void)
{
    char polecenie[MAX_LEN];
    struct Osoba* osoby[MAX_PERSON_COUNT];
    unsigned int n, i, wiek, zaslugi, szelmostwa;
    int indeks = 0;
    char imie[MAX_LEN];
    
    while(1)
    {
        printf("Podaj polecenie: \n");
        fgets(polecenie, MAX_LEN, stdin);

        if (strncmp(polecenie, "0", 1) == 0)
        {
            wyswietl_instrukcje();
        }
        else if (strncmp(polecenie, "1", 1) == 0)
        {
            if (sscanf(polecenie, "1 %u", &n) == 1 && n <= (unsigned int) MAX_PERSON_COUNT - indeks)
            {
                for (unsigned int i = 0; i < n; i++)
                {  
                    printf("Wczytuję dane dla osoby %u\n", i);
                    fgets(polecenie, MAX_LEN, stdin);
                    if (sscanf(polecenie, "%u %u %u %[^\n]", &wiek, &zaslugi, &szelmostwa, imie) == 4)
                    {
                        osoby[indeks] = nowa_osoba(imie, wiek);
                        if (osoby[indeks] != NULL)
                        {
                            ustaw_statystyki(osoby[indeks], zaslugi, szelmostwa);
                            indeks++;
                        }
                        else printf("Nie udało się stworzyć osoby\n");
                        
                    } 
                    else bledne_dane();
                }
            } 
            else bledne_dane();

        }
        else if (strncmp(polecenie, "2", 1) == 0)
        {
            for (int i = 0; i < indeks; i++)
            {
                wypisz_info(osoby[i]);
            }
            qsort(osoby, indeks, sizeof(struct Osoba*), (int (*)(const void*, const void*))komparator);
            for (int i = 0; i < indeks; i++)
            {
                wypisz_info(osoby[i]);
            }
        }
        else if (strncmp(polecenie, "3", 1) == 0)
        {
            for (int i = 0; i < indeks; i++)
            {
                wypisz_info(osoby[i]);
            }
        }
        else if (strncmp(polecenie, "4", 1) == 0)
        {
            if (sscanf(polecenie, "4 %u %u", &i, &wiek) == 2)
            {
                zmien_wiek(osoby[i], wiek);
            }
            else bledne_dane();
            
        }
        else if (strncmp(polecenie, "5", 1) == 0)
        {
            if (sscanf(polecenie, "5 %u %[^\n]", &i, imie) == 2)
            {
                zmien_imie(osoby[i], imie);
            }
            else bledne_dane();
        }
        else if (strncmp(polecenie, "6", 1) == 0)
        {
            if (sscanf(polecenie, "6 %u", &i) == 1)
            {
                dodaj_zasluge(osoby[i]);
            }
            else bledne_dane();
            
        }
        else if (strncmp(polecenie, "7", 1) == 0)
        {
            if (sscanf(polecenie, "7 %u", &i) == 1)
            {
                dodaj_szelmostwo(osoby[i]);
            }
            else bledne_dane();
            
        }
        else if (strncmp(polecenie, "8", 1) == 0)
        {
            if (sscanf(polecenie, "8 %u %u %u", &i, &zaslugi, &szelmostwa) == 3)
            {
                ustaw_statystyki(osoby[i], zaslugi, szelmostwa);
            }
            else bledne_dane();
        }
        else if (strncmp(polecenie, "9", 1) == 0)
        {
            if (sscanf(polecenie, "9 %u", &i) == 1)
            {
                wypisz_info(osoby[i]);
            }
            else bledne_dane();
        }
    }
    return 0;
}

void wyswietl_instrukcje()
{
    printf("Dostepne polecenia:\n");
    printf("0 - wyświetl krótką instrukcję obsługi\n");
    printf("1 N - wczytaj dane o N osobach, które muszą wtedy być podane w N kolejnych liniach, zawierających na początku wiek, zasługi i szelmostwa (liczby nieujemne), a potem imię\n");
    printf("2 - posortuj dane\n");
    printf("3 - wypisz dane\n");
    printf("4 i w - zmień wiek osoby o indeksie i na wartość w\n");
    printf("5 i n - zmień imię osoby o indeksie i na wartość n\n");
    printf("6 i - dodaj zasługę osobie o indeksie i\n");
    printf("7 i - dodaj szelmostwo osobie o indeksie i\n");
    printf("8 i z s - ustaw statystyki osobie o indeksie i na z (zasługi) i s (szelmostwa)\n");
    printf("9 i - wypisz informacje o osobie o indeksie i\n");
}

void bledne_dane()
{
    printf("Nieprawidlowe dane, sprobuj ponownie.\n");
}

