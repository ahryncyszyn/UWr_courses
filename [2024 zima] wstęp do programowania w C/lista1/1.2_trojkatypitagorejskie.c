#include <stdio.h>

int ileTrojkatowPitagorejskich(int M)
{
    int a, b, c;
    int ileTrojkatowP = 0;

    for (a = 1; a <= (M / 2); a++)
    {
        for (b = a; b <= ((M - a) / 2); b++)
        {
            c = M - a - b;
            if (a*a + b*b == c*c)
            {
                ileTrojkatowP++;
            }

        }
    }
    return ileTrojkatowP;
}

int main(void)
{
    // wczytanie zmiennej N
    int N = 0;
    while(N < 12)
    {
        printf("Podaj liczbe naturalna wieksza lub rowna 12: \n");
        scanf("%d", &N);
    }

    // zdefiniowanie zmiennych pomocniczych
    int najlepszeM = 12;
    int najwiecejTrojkatow = 0;
    
    // zaczynamy od 12, dla mniejszych M nie da się
    // stworzyć trojkata pitagorejskiego
    int M = 12;

    // sprawdzenie wszystkich 12 <= M <= N
    while (M <= N)
    {
        int ileTrojkatowP = ileTrojkatowPitagorejskich(M);
        if (ileTrojkatowP > najwiecejTrojkatow)
        {
            najwiecejTrojkatow = ileTrojkatowP;
            najlepszeM = M;
        }
        M++;
    }

    printf("Najwiecej trojkatow pitagorejskich jest dla M = %d, jest ich %d\n.", najlepszeM, najwiecejTrojkatow);
    return 0;
}