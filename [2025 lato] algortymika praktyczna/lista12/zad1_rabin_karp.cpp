#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;

int p = 31;
int mod = 1000000007;
vector<ull> p_powers;
vector<ull> p_powers_inv;
vector<ull> prefixes;
vector<ull> suffixes;

ull power(ull a, ull b)
{
    ull res = 1;
    while (b)
    {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

ull calculate_hash(string& s)
{
    ull hash = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        hash = (hash + (s[i] - 'a' + 1) * p_powers[i]) % mod;
    }
    return hash;
}

ull get_substring_hash(int i, int j)
{
    if (i == 0) return prefixes[j];
    ull hash = (suffixes[j] - prefixes[i]) * p_powers_inv[i - 1] % mod;
    return hash;
}

int rabin_karp(string& word, string& pattern)
{
    int pattern_len = pattern.size();
    string first_fragment = word.substr(0, pattern_len);

    ull pattern_hash = calculate_hash(pattern);
    int count = 0;

    for (int i = 0; i <= (int)word.size() - pattern_len; i++)
    {
        ull sub_hash = get_substring_hash(i + 1, i + pattern_len);
        if (sub_hash == pattern_hash)
        {
            count++;
        }
    }
    return count;
}

void preprocessing(string& word)
{
    int n = word.size();
    p_powers.resize(n);
    p_powers_inv.resize(n);
    prefixes.resize(n);
    suffixes.resize(n);

    p_powers[0] = 1;
    p_powers_inv[0] = 1;
    prefixes[0] = (word[0] - 'a' + 1);

    for (int i = 1; i < (int)word.size(); i++)
    {
        p_powers[i] = (p_powers[i - 1] * p) % mod;
        p_powers_inv[i] = power(p_powers[i], mod - 2);
        prefixes[i] = (prefixes[i - 1] + ((word[i] - 'a' + 1) * p_powers[i]) % mod) % mod;
    }
    suffixes[n - 1] = (word[n - 1] - 'a' + 1) * p_powers[n - 1];
    for (int i = n - 2; i >= 0; i++)
    {
        suffixes[i] = (suffixes[i + 1] + ((word[i] - 'a' + 1) * p_powers[n - i - 1]) % mod) % mod;
    }
}

int main()
{
    string word, pattern;
    cin >> word >> pattern;
    if (pattern.size() > word.size()) 
    {
        cout << 0;
        return 0;
    }
    preprocessing(word);
    cout << rabin_karp(word, pattern);
    return 0;
}