#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007
#define MAX_A 1000000

long long fast_exp(long long a, long long N)
{
    long long res = 1;
    while (N > 0)
    {
        if (N & 1)
        {
            res = (res * a) % MOD;
        } 
        N >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}

long long binomial_coeff(int a, int b, vector<long long> &fact, vector<long long> &inv_fact)
{
    return ((fact[a] * inv_fact[b]) % MOD * inv_fact[a-b] % MOD) % MOD;
}

int main()
{
    cout.tie(0);
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    // tablica z silniami
    vector<long long> fact(MAX_A + 1, 1);
    for (int i = 2; i <= MAX_A; i++) 
    {
        fact[i] = fact[i-1] * i % MOD;
    }

    // tw. fermata: x^-1 = x^(MOD - 2) % MOD
    // (a * b) mod c = ((a mod c) * (b mod c)) mod c
    // (a!)^-1 = ((a-1)!)^-1 * (a)^-1 :)
    vector<long long> inv_fact(MAX_A + 1, 1);
    inv_fact[MAX_A] = fast_exp(fact[MAX_A], MOD - 2);
    for (int i = MAX_A - 1; i >= 1; i--)
    {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD; 
    }
    inv_fact[0] = 1;
    
    // wypisywanie wynikow
    int a, b;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        cout << binomial_coeff(a, b, fact, inv_fact) << endl;
    }
    return 0;
}