
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// w krolestwie jest n miast wzdluz jednej drogi
// miasto i sasiaduje z i-1 oraz i+1, miasta 1 i n rowniez sasiaduja
// w miescie i co j(i) dni organizowany jest targ
// w miescie i co m(i) dni jest mega-targ, gdzie m(i) to NWW(j(i-1), j(i), j(i+1))
// pytanie 1: jakie jest najmniejsze k, takie ze po k dniach bedzie przynajmniej r mega-targow?
// pytanie 2: ile najmniej miast musi organizowac mega-targi zeby 
//            do dnia p odbylo sie ich przynjamniej q?

// wejscie: n <= 100 000 - liczba miast
//          n liczb naturalnych <= 1 000 000 - kolejne j(i)
//          r, p, q <= 1 000 000 000 
// wyjscie: dwie odpowiedzi na pytanie krola

long long NWW(long long a, long long b);
long long NWD(long long a, long long b);
int compare(const void* a, const void* b);

int main(void)
{
    // wczytanie zmiennych
    int n;
    long long r, p, q, k;
    k = scanf("%d", &n);

    int* j = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        k = scanf("%d", &j[i]);
    }
    k = scanf("%lld%lld%lld", &r, &p, &q);

    // obliczenie m(i)
    long long* m = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        long long left = (i == 0) ? j[n - 1] : j[i - 1];
        long long right = (i == n - 1) ? j[0] : j[i + 1];
        m[i] = NWW(j[i], NWW(left, right));
    }

    // posortowanie czestotliwosci orgainzowania mega-targow
    qsort(m, n, sizeof(long long), compare);

    // obliczenie k - po k dniach bedzie min r targow
    k = 0;
    long long min = 0, max = m[0] * r, mid;
    long long targi = 0;

    while (min <= max)
    {
        mid = (min + max) / 2;
        
        targi = 0;
        for (int i = 0; i < n; i++)
        {
            targi += (mid / m[i]);
            if (targi > r) break;
        }

        if (targi >= r) 
        {
            k = mid;
            max = mid - 1;
        }
        else min = mid + 1;
    }

    // obliczenie ile miast musi organizowac mega targi zeby do dnia p odbylo sie ich q
    int miasta = 0;
    targi = 0;
    while (targi < q)
    {
        miasta++;
        targi += (p / m[miasta-1]);
    }
    printf("%lld %d", k, miasta);
    free(j); free(m);

    return 0;

}

int compare(const void* a, const void* b) {
    long long int_a = *(long long*)a;
    long long int_b = *(long long*)b;

    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

long long NWW(long long a, long long b) {
    return (a / NWD(a, b)) * b;
}

long long NWD(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

