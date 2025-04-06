#include "drzewo_het.h"

void n_queens_tree(Node* curr, int col, int b[], int n);
int is_being_attacked(int x, int y, int b[]);

int main(int argc, char* argv[])
{
    // weryfikowanie argumentow wywolania
    if (argc != 2)
    {
        printf("Niepoprawna ilość argumentow wywolania\n");
        return 1;
    }

    // weryfikowanie liczby hetmanow
    char* pKoniec;
    long n = strtol(argv[1], &pKoniec, 10);
    if (n <= 0 || (*pKoniec) != '\0')
    {
        printf("Nieprawidłowy argument, prosze podać liczbę naturalną dodatnią\n");
        return 1;
    }

    // tablica b przechowuje wiersz pozycji hetmana w kazdej kolumnie
    // inicjalizowana na -1, czyli brak hetmana w zadnej kolumnie
    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL)
    {
        printf("Alokowanie pamieci sie nie powiodlo\n");
        return 1;
    }
    for (int i = 0; i < n; i++) b[i] = -1;

    // pierwszy element drzewa jest tylko pomocniczy - pozycja (-1, -1) nie istnieje
    Node* root = create_node(-1, -1, 0, 0);

    // znalezienie rozwiazania problemu hetmanow
    // i zapisanie go w formie drzewa decyzyjnego
    n_queens_tree(root, 0, b, n);

    // drukowanie drzewa
    print_tree(root, -1);

    // zwalnianie pamieci
    free(b);
    free_node(root);

    return 0;
}

void n_queens_tree(Node* curr, int col, int b[], int n)
{
    // znaleziono rozwiazanie
    if (col == n)
    {
        curr -> is_solution = 1;
        return;
    }

    // szukanie miejsca na kolejnego hetmana w kazdym rzedzie
    int attacking_col;
    for (int row = 0; row < n; row++)
    {
        // sprawdzanie czy obecna pozycja jest atakowana
        attacking_col = is_being_attacked(row, col, b);

        Node* child = create_node(col, row, attacking_col, 0);
        add_child(curr, child);

        // pozycja nie jest atakowana
        if (attacking_col == -1)
        {
            // ustawiamy hetmana
            b[col] = row;
            n_queens_tree(child, col + 1, b, n);
        }
    }
}

int is_being_attacked(int row, int col, int b[])
{
    // sprawdza wszystkie poprzednie kolumny
    for (int prev_col = 0; prev_col < col; prev_col++)
    {
        // zwraca numer kolumny w ktorej jest hetman atakujacy dana pozycje
        if (b[prev_col] - prev_col == row - col || b[prev_col] + prev_col == col + row || b[prev_col] == row) return prev_col;
    }
    return -1;
}