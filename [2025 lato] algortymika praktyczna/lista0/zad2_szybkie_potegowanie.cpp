#include <iostream>

#define MOD 1000000000

// (a * b) mod c = (a mod c * b mod c) mod c
// a = c * q1 + r1
// b = c * q2 + r2
// L = ((c * q1 + r1) * (c * q2 + r2)) mod c
//   = ((c * c * q1 * q1) + (c * q1 * r2) + (c * q2 * r1) + (r1 * r2)) mod c
//   = (c (c * q1 * q2 + q1 * r2 + q2 * r1 ) + (r1 * r2)) mod c
//   = (r1 * r2) mod c = R

// zlozonosc czasowa: O(log(N))
// bo liczba iteracji zalezy od dlugosci repr. binarnej N
long long fast_exp(long long a, long long N)
{
    long long res = 1;
    while (N > 0)
    {
        if (N % 2 == 1)
        {
            res = (res * a) % MOD;
        } 
        N = N / 2;
        a = (a * a) % MOD;
    }
    return res % MOD;
}

int main()
{
    long long a, N;
    std::cin >> a >> N;
    std::cout << fast_exp(a, N);
    return 0;
}