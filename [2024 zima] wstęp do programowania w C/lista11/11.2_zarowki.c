#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ENERGY 9
#define MIN_ENERGY 0

int flashes(int*** lightbulbs, int*** have_flashed, long long* flashes_count, int n);
bool increase_surrounding(int*** lightbulbs, int*** have_flashed, int i, int j, int n);

int main()
{
    // n - wymiary siatki zarowek (nxn)
    // m - liczba krokow (dni)
    int n, m;
    scanf("%d%d", &n, &m);

    // poczatkowe enegie zarowek
    int** lightbulbs = (int**)malloc(sizeof(int*) * n);
    if (lightbulbs == NULL) return 0;
    for (int i = 0; i < n; i++)
    {
        lightbulbs[i] = (int*)malloc(sizeof(int) * n);
        if (lightbulbs[i] == NULL)
        {
            for (int j = 0; j < i; j++) free(lightbulbs[j]);
            free(lightbulbs);
            return 0;
        }

        for (int j = 0; j < n; j++)
        {
            char ch = getchar();
            while (ch == '\n' || ch == ' ') 
            {
                ch = getchar();
            }
            lightbulbs[i][j] = ch - '0';
        }
    }

    // tabela na informacje ktore zarowki juz rozlbysly w danym kroku
    int** have_flashed = (int**)calloc(n, sizeof(int*));
    if (have_flashed == NULL) return 0;
    for (int i = 0; i < n; i++)
    {
        have_flashed[i] = (int*)calloc(n, sizeof(int));
        if (have_flashed[i] == NULL)
        {
            for (int j = 0; j < i; j++) free(have_flashed[j]);
            free(have_flashed);
            return 0;
        }
    }


    // zliczanie rozblyskow po m dniach
    long long flashes_count = 0;
    for (int day = 0; day < m; day++)
    {
        // wyzerowanie have_flashed
        for (int i = 0; i < n; i++) for (int  j = 0; j < n; j++) have_flashed[i][j] = 0;
        
        // dodanie 1 do energii kazdej zarowki
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                lightbulbs[i][j]++;
            }
        } 

        // sprawdzanie czy jakas rozblysla
        bool more_to_flash = 0;
        do{
            more_to_flash = flashes(&lightbulbs, &have_flashed, &flashes_count, n);
        } while (more_to_flash);
    }

    printf("%lld", flashes_count);

    // zwalnianie pamieci
    for (int i = 0; i < n; i++) free(lightbulbs[i]);
    for (int i = 0; i < n; i++) free(have_flashed[i]);
    free(lightbulbs); free(have_flashed);
    return 1;
}

int flashes(int*** lightbulbs, int*** have_flashed, long long* flashes_count, int n)
{
    bool more_to_flash = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((*lightbulbs)[i][j] > MAX_ENERGY
                && !(*have_flashed)[i][j])
            {
                (*flashes_count)++;
                (*have_flashed)[i][j] = 1;
                (*lightbulbs)[i][j] = MIN_ENERGY;
                if (increase_surrounding(lightbulbs, have_flashed, i, j, n))
                {
                    more_to_flash = 1;
                }
            }
        }
    }
    return more_to_flash;
}

bool increase_surrounding(int*** lightbulbs, int*** have_flashed, int i, int j, int n)
{
    bool more_to_flash = 0;
    int new_i, new_j;
    for (int x = -1; x <= 1; x++) 
    {
        for (int y = -1; y <= 1; y++) 
        {
            if (x == 0 && y == 0) continue;

            new_i = i + x;
            new_j = j + y;
            if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < n 
                && !(*have_flashed)[new_i][new_j]) 
            {
                (*lightbulbs)[new_i][new_j]++;
                if ((*lightbulbs)[new_i][new_j] > MAX_ENERGY)
                {
                    more_to_flash = 1;
                }
            }
        }
    }
    return more_to_flash;
}