#include "wiersze.h"

char* readline()
{
    // alokowanie bufora na caly wiersz
    size_t buffer_size = 128;
    size_t input_length = 0;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL)
    {
        printf("Alokowanie pamieci się nie powiodło\n");
        return NULL;
    }
    // wczytywanie wejscia do bufora
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // zwiększenie zalokowanej pamięci na wiersz
        // z uwglednieniem miejsca na '\0'
        if (input_length + 1 >= buffer_size)
        {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (new_buffer == NULL)
            {
                free(buffer);
                printf("Alokowanie pamieci się nie powiodło\n");
                return NULL;
            }
            buffer = new_buffer;
        }
        // dodanie wczytanego znaku do bufora
        buffer[input_length] = c;
        input_length++;
    }
    // zwrocenie NULL jezeli wiersz jest pusty
    if (input_length == 0) 
    {
        free(buffer);
        return NULL;
    }

    buffer[input_length] = '\0';
    return buffer;
}

char** parse_words(char* buffer)
{
    if (!buffer) return NULL;
    size_t buffer_size = strlen(buffer); // liczba znakow w buforze

    // alokowanie tablicy na słowa
    size_t words_limit = 10;
    char** line = (char**)malloc(words_limit * sizeof(char*));
    if (line == NULL)
    {
        printf("Alokowanie pamieci się nie powiodło\n");
        return NULL;
    }

    size_t word_len = 0; // liczba znakow w slowie
    size_t position = 0; // pozycja w buforze wejsciowym
    size_t word_start; // pozycja poczatku nowego slowa
    size_t words_count = 0; // liczba slow w tablicy wiersz
    while (position < buffer_size)
    {   
        // omijanie spacji na poczatku
        while (position < buffer_size && !isgraph(buffer[position])) position++;
        if (position == buffer_size) break;

        // zwiekszenie zalokowanej pamieci na slowa
        // z uwzglednieniem dodatkowej pamieci na wartownika na koncu
        if (words_count + 1 >= words_limit)
        {
            words_limit *= 2;
            char** nowy_wiersz = realloc(line, words_limit * sizeof(char*));
            if (nowy_wiersz == NULL)
            {
                printf("Alokowanie pamieci się nie powiodło\n");
                for (size_t i = 0; i < words_count; i++) free(line[i]);
                free(line);
                return NULL;
            }
            line = nowy_wiersz;
        }

        // szukanie nowego słowa
        word_start = position;
        while (position < buffer_size && isgraph(buffer[position]))
        {
            position++;
        }
        word_len = position - word_start;

        // alokowanie pamięci na słowo
        line[words_count] = (char*)malloc((word_len + 1) * sizeof(char));
        if (line[words_count] == NULL)
        {
            printf("Alokowanie pamieci się nie powiodło\n");
            for (size_t i = 0; i < words_count; i++) free(line[i]);
            free(line);
            return NULL;
        }
        // kopiowanie slowa z bufora do tablicy ze słowami
        strncpy(line[words_count], &buffer[word_start], word_len);
        line[words_count][word_len] = '\0';
        words_count++;
    }

    // dodanie wartowanika na koniec tablicy ze słowami
    line[words_count] = NULL;
    return line;  
}

int compare_lines(const void *a, const void *b)
{
    char **wiersz1 = *(char ***)a; 
    char **wiersz2 = *(char ***)b;

    // szukanie ostatniego slowa w kazdym wierszu
    int i = 0, j = 0;
    while (wiersz1[i] != NULL) i++;
    while (wiersz2[j] != NULL) j++;

    int comparison;
    while (i > 0 && j > 0)
    {
        i--; j--;
        comparison = strcmp(wiersz1[i], wiersz2[j]);
        if (comparison != 0) return comparison;
    }

    // jezeli nie sa rowne to zwrocenie wiersza z mniejsza iloscia slow jako mniejszego
    return (i <= 0 && j <= 0) ? 0 : (i <= 0 ? -1 : 1);
}

#ifdef USE_QSORT
void sort_lines(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *))
{
    printf("\nQuicksort!\n");
    qsort(all_lines, lines_count, sizeof(char**), compare_lines);
}

#else
// 353636 mod 3 = 2, wiec sortowanie przez wybor
void selection_sort(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *))
{
    printf("\nSortowanie przez wybor!\n");
    for (size_t i = 0; i < lines_count - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < lines_count; j++)
        {
            if (compare_lines(&all_lines[j], &all_lines[min_idx]) < 0) min_idx = j;
        }
        if (min_idx != i) 
        {
            char** temp = all_lines[i];
            all_lines[i] = all_lines[min_idx];
            all_lines[min_idx] = temp;
        }
    }
    
}

void sort_lines(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *))
{
    selection_sort(all_lines, lines_count, compare_lines);
}
#endif

void free_all_lines(char*** all_lines, size_t lines_count)
{
    for (size_t i = 0; i < lines_count; i++) 
    {
        for (size_t j = 0; all_lines[i][j] != NULL; j++)
        {
            free(all_lines[i][j]);
        }
        free(all_lines[i]);
    }
    free(all_lines);
}


