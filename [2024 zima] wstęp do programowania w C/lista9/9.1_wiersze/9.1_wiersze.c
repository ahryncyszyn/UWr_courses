#include "wiersze.h"

int main()
{
    // alokowanie tablicy na wiersze ze slowami
    size_t lines_count_limit = 8;
    size_t lines_count = 0;
    char*** all_lines = malloc(lines_count_limit * sizeof(char**));
    if (all_lines == NULL)
    {
        printf("Alokowanie pamieci się nie powiodło\n");
        return 1;
    }

    // wczytywanie danych
    char* buffer;
    char** nowy_wiersz;
    while ((buffer = readline()) != NULL)
    {
        // zwiekszanie zalokowanej pamieci na wiersze
        if (lines_count >= lines_count_limit)
        {
            lines_count_limit *= 2;
            char*** new_lines = realloc(all_lines, lines_count_limit * sizeof(char**));
            if (new_lines == NULL)
            {
                printf("Alokowanie pamieci się nie powiodło\n");
                free_all_lines(all_lines, lines_count);
                return 1;
            }
            all_lines = new_lines;
        }
        
        // dodanie tablicy ze slowami w wierszu do tablicy z wierszami
        nowy_wiersz = parse_words(buffer);
        if (nowy_wiersz == NULL)
        {
            printf("Alokowanie pamieci dla wiersza %s się nie powiodło\n", buffer);
            printf("Sortowanie pozostałych wczytanych wierszy\n");
            break;
        }
        all_lines[lines_count] = nowy_wiersz;
        lines_count++;
        free(buffer);
    }

    // sortowanie wierszy
    sort_lines(all_lines, lines_count, compare_lines);

    // wypisywanie posortowanych wierszy i zwalnianie pamieci
    printf("Po sortowaniu kolejność wierszy to:\n");
    for (size_t i = 0; i < lines_count; i++)
    {
        for (size_t j = 0; all_lines[i][j] != NULL; j++)
        {
            printf("%s ", all_lines[i][j]);
            free(all_lines[i][j]);
        }
        printf("\n");
        free(all_lines[i]);
    }
    free(all_lines);
    
    return 0;
}