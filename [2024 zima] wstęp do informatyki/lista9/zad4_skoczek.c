#include <stdio.h>

#define N 5

// sprawdza czy mozna wykonac danych ruch
int isSafe(int x, int y, int sol[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N
            && sol[x][y] == -1);
}

void printSolution(int sol[N][N])
{
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

// x, y = wsporzedne pozycji
// movei = aktualny licznik krokow
// sol[N][N] = tablica z krokami
int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[N], int yMove[N])
{
    int k, next_x, next_y; // zmienne na kolejne kroki
    if (movei == N * N) return 1; // base case: liczba ruchow rowna liczbie pol

    // sprawdzanie wszystkich mozliwych kolejnych ruchow
    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol)) // jezeli ruch jest mozliwy
        {
            sol[next_x][next_y] = movei; // zapisz indeks kroku w tablicy
            // jezeli mozna znalezc rozwiazanie z tej pozycji, zwroc 1
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove) == 1) return 1; 
            else
                // jezeli nie mozna znalezc rozwiazania, cofnij ten krok i sprawdzaj kolejny
                sol[next_x][next_y] = -1;
        }
    }
    return 0;
}

int solveKT()
{
    int sol[N][N];

    // inicjalizowanie tablicy na -1 
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    // xMove[] and yMove[] define the next move of the
    // knight xMove[] is for the next value of x coordinate
    // yMove[] is for the next value of y coordinate
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    // pozycja startowa skoczka
    sol[0][0] = 0;

    // rekursywne szukanie mozliwych tras
    if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0) {
        printf("Solution does not exist");
        return 0;
    }
    else
        printSolution(sol);

    return 1;
}

int main()
{
    solveKT();
    return 0;
}