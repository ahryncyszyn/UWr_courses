// Aleksandra Hryncyszyn, 353636
// lista 4, zad 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 25

int power(int podstawa, int potega);
int compare_strings(char *str1, char *str2);
void generate_subsequences(char *sequence, int start, char *current, int current_len, char subsequences[][MAX_LEN], int *subs_count);

// argv = sciezka, ciag znakow S, flaga (opcjonalne)
int main(int argc, char *argv[])
{
    // zweryfikowanie liczby argumentow
    if (argc > 4 || argc < 2)
    {
        printf("Niepoprawna liczba argumentow\n");
        return 1;
    }

    // wczytanie ciagu S
    char *sequence = argv[1];
    int length = strlen(sequence);

    // stworzenie tablicy do przechowywania podciagow
    char subsequences[power(2, length)][MAX_LEN];
    int subs_count = 0;

    // generowanie podciagow
    int start = 0;
    char current[MAX_LEN];
    generate_subsequences(sequence, start, current, 0, subsequences, &subs_count);

    // wypisanie wyniku w zaleśności od uzytej flagi
    if (argc == 2)
    {
        srand(time(NULL));
        int random_index = rand() % subs_count;
        printf("%d\n", random_index + 1);
        printf("%s\n", subsequences[random_index]);
    }
    else if (argc == 3 && compare_strings(argv[2], "-a"))
    {
        for (int i = 0; i < subs_count; i++) 
        {
            printf("%s\n", subsequences[i]);
        }
    }
    else if (argc == 4 && compare_strings(argv[2], "-i"))
    {
        int index = atoi(argv[3]);
        if (index <= 0)
        {
            printf("Argument dla wywołania z flagą -i powininen być dodatnią liczbą naturalną\n");
            return 1;
        }
        if (index > subs_count)
        {
            printf("Podany indeks przekracza liczbę podciągow\n");
            return 1;
        }
        printf("%s\n", subsequences[index - 1]);

    } else
    {
        printf("Niepoprawne wywołanie\n");
        return 1;
    }
    return 0;
}

void generate_subsequences(char *sequence, int start, char *curr_subs, int current_len, char subsequences[][MAX_LEN], int *subs_count)
{   
    // sequence = wejsciowy ciag znakow, start = indeks od ktorego generujemy podciagi
    // curr_subs = obecnie rozwazany podciag, current_len = dlugosc obecnie rozwazanego podciagu
    // subsequences = tablica 2D gdzie zapisywane sa podciagi
    // subs_count = liczba juz zapisanych podciagow

    if (current_len > 0) 
    {
        // zapisujemy podciagi do tablicy subsequences
        for (int i = 0; i < current_len; i++)
        {
            subsequences[*subs_count][i] = curr_subs[i];
        }
        subsequences[*subs_count][current_len] = '\0';

        // zwiekszamy licznik podciagow
        (*subs_count)++;
    }

    // sprawdzamy rekursywnie wszystkie kolejne mozliwosci az do konca ciagu
    for (int i = start; sequence[i] != '\0'; i++) 
    {
        // dodajemy nowy znak do obecnego podciagu
        curr_subs[current_len] = sequence[i];
        // wywolujemy funkcje ze zwiekszonym indeksem start i obecna dlugoscia podciagu
        generate_subsequences(sequence, i + 1, curr_subs, current_len + 1, subsequences, subs_count); 
    }
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

int power(int podstawa, int potega)
{
    int res = 1;
    while (potega > 0)
    {
        if (potega % 2 == 1)
            res *= podstawa;
        podstawa *= podstawa;
        potega /= 2;
    }
    return res;
}