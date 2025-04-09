#include <stdio.h>

// Wejscie: n, m - liczby naturalne
// Wyjscie: T(n), gdzie:
// T(n, 0) = n dla n ≥ 0
// T(0, m) = m dla m > 0
// T(n, m) = T(n − 1, m) + 2T(n, m − 1) w przeciwnym przypadku.

int TnR(int n, int m)
{
    if (!m) return n;
    if (!n) return m;

    return TnR(n - 1, m) + 2 * TnR(n, m - 1);
}

int TnInotopt(int n, int m)
{
    if (!m) return n;
    if (!n) return m;

    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j] + 2 * dp[i][j - 1];
        }
    }
    return dp[n][m];
}


int TnI(int n, int m)
{
    int TM[m+1];
    int n_pom = 0, m_pom = 0;

    while (n_pom <= n)
    {
        m_pom = 0;
        while (m_pom <= m)
        {
            if (m_pom == 0) TM[m_pom] = n_pom;
            else if (n_pom == 0) TM[n_pom] = m_pom;
            else TM[m_pom] = TM[m_pom] + 2 * TM[m_pom-1];
            m_pom++;
        }
        n_pom++;
    }
    return TM[m];
}


int main(void)
{
    int n = 3, m = 4;
    printf("wynik to: %d i %d\n", TnI(n, m), TnR(n, m));
    return 0;
}

// dla 3 i 4 wynik to 486
/*

                         T(3,4)
                  /               \
              T(2,4)            2*T(3,3)
              /     \           /         \
          T(1,4)  2*T(2,3)   T(2,3)  2*T(3,2)

*/