#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// wczytuje cały wiersz do dynamicznie alokowanego bufora
// zwraca pointer do bufora
char* readline();

// dzieli wiersz na osobne słowa, oddzielone przez białe znaki
// zwraca pointer do tablicy zawierającej pointery na tablice z kolejnymi słowami
char** parse_words(char* buffer);

// zwalnia pamięć z całej tablicy zawierającej wiersze zawierające słowa
void free_all_lines(char*** line, size_t lines_count);

// porownuje wiersze od ostatniego słowa
int compare_lines(const void *a, const void *b);

// funkcje sortujace wiersze
#ifdef USE_QSORT
void sort_lines(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *));
#else
void sort_lines(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *));
void selection_sort(char*** all_lines, size_t lines_count, int (*compare_lines)(const void *, const void *));
#endif