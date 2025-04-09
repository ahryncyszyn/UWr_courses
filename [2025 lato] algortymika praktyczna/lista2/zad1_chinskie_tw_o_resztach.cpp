#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// zwraca k i l t.z. ak + bl = 1 (mod b)
// wiec ak = 1 (mod b)
// wiec k = a^-1 (mod b)
int extended_gcd(ll a, ll b, ll& k, ll& l)
{
    if (b == 0)
    {
        k = 1;
        l = 0;
        return a;
    }

    ll prev_k, prev_l;
    ll g = extended_gcd(b, a % b, prev_k, prev_l);

    k = prev_l;
    l = prev_k - (a / b) * prev_l;
    return g;
}

// M = p1 * p2 * ...
// szukamy w t.z. wi mod pi = ai ^ wi mod pj = 0
// wtedy x = (w1 + w2 + ...) mod M
// 
void solve_equations(vector<int> &primes, vector<int> &remainders, int K)
{
    ll M = 1;
    for (int i = 0; i < K; i++) M *= primes[i];

    ll res = 0, m_i, m_i_inv, k, l;
    for (int i = 0; i < K; i++)
    {
        m_i = M / primes[i];

        extended_gcd(m_i, primes[i], k, l);
        m_i_inv = (k % primes[i]);
        if (m_i_inv < 0) m_i_inv = (m_i_inv + primes[i]) % primes[i];

        res += ((remainders[i] * m_i) % M * m_i_inv) % M;   
    }
    cout << res % M << '\n';
}

int main()
{
    cout.tie(0); cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N, K;
    cin >> N;

    vector<int> primes(12);
    vector<int> remainders(12);
    for (int i = 0; i < N; i++)
    {
        cin >> K;
        for (int j = 0; j < K; j++)
        {
            cin >> primes[j] >> remainders[j];
        }
        solve_equations(primes, remainders, K);
    }
    return 0;
}