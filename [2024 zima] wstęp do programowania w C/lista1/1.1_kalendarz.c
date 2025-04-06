#include <stdio.h>
#include <stdbool.h>

int main(void){

// wczytanie prawidlowych zmiennych
int rok = 0, miesiac = 0, dzien = 0;
while (rok <= 0)
{
    printf("Podaj rok:\n");
    scanf("%d", &rok);
}
while (miesiac <= 0 || miesiac > 12)
{
    printf("Podaj miesiac (1-12):\n");
    scanf("%d", &miesiac);
}
while (dzien <= 0 || dzien > 7)
{
    printf("Podaj pierwszy dzien miesiaca (1-7):\n");
    scanf("%d", &dzien);
}

// wyznaczenie liczby dni danego miesiaca
int liczbaDni;
bool rokPrzestepny = ( ((rok % 4 == 0) & (rok % 100 != 0)) || (rok % 400 == 0) );
if ((miesiac == 2) & rokPrzestepny)
{
    liczbaDni = 29;
} else if (miesiac == 2)
{
    liczbaDni = 28;
} else if (miesiac == 4 || miesiac == 6 || miesiac == 9 || miesiac == 11)
{
    liczbaDni = 30;
} else
{
    liczbaDni = 31;
}

// stworzenie tablicy do przechowywania dni
int kalendarz[6][7] = {0};
int i = 1;
while (i <= liczbaDni)
{
    // jednak trzeba przesuwac o dwa, bo nie tylko bierzemy
    // poprawke na liczenie od zera, ale tez na to,
    // ze dzien = 1 oznacza zerowe przesuniecie
    int rzad = (i + dzien - 2) / 7;
    int kolumna = (i + dzien - 2) % 7;
    kalendarz[rzad][kolumna] = i;
    i++;
}

// printowanie tablicy
for (int a = 0; a < 6; a++)
{
    for (int b = 0; b < 7; b++)
    {
        if (kalendarz[a][b] == 0)
        {
        printf("   ");
        } else
        {
        printf("%2d ", kalendarz[a][b]);
        }
    }
    printf("\n");
}

return 0;
}
