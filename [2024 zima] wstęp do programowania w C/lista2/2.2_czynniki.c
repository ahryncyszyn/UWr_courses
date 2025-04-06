#include <stdio.h>
#include <limits.h>

int threeMinNums(int, int*, int*, int*);
int maxUnevenFactors(int);

int main(void)
{
    // wczytanie n, liczby liczb na wejsciu
    int n = 0;
    while (n < 3)
    {
        printf("Podaj liczbe naturalna wieksza lub rowna 3: \n");
        while (scanf("%d", &n) < 1) getchar(); 
    }

    // zakladamy, ze min1 <= min2 <= min3
    int min1 = INT_MAX, min2 = INT_MAX, min3 = INT_MAX;

    // funkcja do wyznaczenia trzech najmniejszych liczb z wejscia
    threeMinNums(n, &min1, &min2, &min3); 
    printf("Najmniejsze trzy liczby to: %d, %d i %d. \n", min1, min2, min3);

    // wyznaczenie ktora z liczb ma najwiecej
    // roznych nieparzystych czynnikow pierwszych
    int nums[3] = {min1, min2, min3};
    int factors[3] = {0};
    int maxFactors = 0;
    for (int i = 0; i < 3; i++)
    {
        factors[i] = maxUnevenFactors(nums[i]);
        if (factors[i] > maxFactors) maxFactors = factors[i];
    }

    // wypisywanie wynikow
    for (int i = 0; i < 3; i++)
    {
        if (factors[i] == maxFactors)
            printf("Liczba z najwieksza liczba roznych nieparzystych czynnikow pierwszych: %d. \n", nums[i]);
    }
}

int threeMinNums(int n, int *min1, int *min2, int *min3)
{
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        // wczytanie liczby z wejscia
        printf("Podaj liczbe calkowita: \n");
        while (scanf("%d", &num) < 1) getchar();

        if (num < *min1)
        {
            *min3 = *min2;
            *min2 = *min1;
            *min1 = num;
        }
        else if (num < *min2)
        {
            *min3 = *min2;
            *min2 = num;
        }
        else if (num < *min3)
        {
            *min3 = num;
        }
    }
    return 0;
}

int maxUnevenFactors(int num)
{
    // zeby petla z usuwaniem parzystych nie byla nieskonczona
    if (num == 0) return 0; 
    if (num < 0) num = -num;

    // pozbywamy sie parzystych czynnikow
    while (num % 2 == 0)
        num /= 2;

    if (num < 3) return 0;
    int counter = 0;

    // sprawdzamy tylko nieparzyste dzielniki
    // dzielniki musza byc rozne, wiec kazdy liczymy tylko raz
    for (int divisor = 3; divisor <= num; divisor += 2)
    {
        if (num % divisor == 0)
        {
            counter++;
            while (num % divisor == 0)
                num /= divisor;
        }
    }
    return counter;
}
