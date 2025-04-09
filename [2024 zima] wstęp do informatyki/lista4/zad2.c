#include <stdio.h>

// najwiekszy wspolny dzielnik (Euklides)
// zloz. czas = O(log2(n+m))
int nwd(int a, int b)
{
    int k;
    while (b != 0)
    {
        // zamieniamy a z b bo (a mod b) < b
        k = a % b; 
        a = b;
        b = k;
    }
    return a;
}

// najmniejsza wspolna wielokrotnosc
int nww(int a, int b)
{
    // nww(48, 20) = nww(2*2*3*4, 2*2*5) = 2*2*3*4*2*2*5 / 2*2 = 2*2*3*4*5 = 240
    return (a / nwd(a, b)) * b;
}

// skrocenie poprzez podzielenie przez najwiekszy wspolny dzielnik
int skrocony_ulamek(int a, int b, int *skrocone_a, int *skrocone_b)
{
    int nwd_ab = nwd(a, b);
    *skrocone_a = a / nwd_ab;
    *skrocone_b = b / nwd_ab;
    return 1;
}

// zloz. czas = O(log(min(a, b)))
// zloz. pam = O(1)
int main(void)
{
    int a, b;
    printf("Podaj liczbe a oraz b\n");
    scanf("%d%d", &a, &b);
    printf("a i b to %d %d\n", a, b);

    int skrocone_a, skrocone_b;
    skrocony_ulamek(a, b, &skrocone_a, &skrocone_b);
    printf("NWW a i b to: %d\n", nww(a, b));
    printf("Skrocony ulamek a/b to: %d %d\n", skrocone_a, skrocone_b);
}