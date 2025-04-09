#include <stdio.h>
// Wejście: n, k – dodatnia liczby całkowite, a1, . . . , ak – liczby naturalne większe od 1
// Wyjście: p – największa liczba naturalna taka, że n jest podzielne przez a^p_i dla jakiegoś i ∈ {1, 2, . . . , k}
//        liczby ze zbioru {a1, . . . , ak} których p-ta potęga jest dzielnikiem n.

int main(void) // O(k*log2(n))
{
    // wczytanie liczby i liczby dzielnikow
    int n, k;
    printf("Podaj liczbe naturalna n \n");
    scanf("%d", &n);
    printf("Podaj liczbe naturalna k (zakres dzielnikow) \n");
    scanf("%d", &k);

    // wczytanie k dzielnikow - O(k)
    int dzielniki[k];
    printf("Podaj k liczb wiekszych od 1 \n");
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &dzielniki[i]);
    }

    // znalezienie potegi dla kazdego dzielnika
    int max_p = 0;
    int potegi[k];
    for (int i = 0; i < k; i++) // O(k)
    {
        int p = 0;
        int temp_n = n;
        while (temp_n > 0 && (temp_n % dzielniki[i]) == 0) // O(log2(n))
        {
            temp_n = temp_n / dzielniki[i];
            p++;
        }

        if (p > max_p) max_p = p;
        potegi[i] = p;
    }

    // wypisanie p oraz dzielnikow z p potega
    printf("Najwieksza p to: %d\n", max_p);
    for (int i = 0; i < k; i++) // O(k)
    {
        if (potegi[i] == max_p)
            printf("%d ", dzielniki[i]);
    }

    return 0;
}
