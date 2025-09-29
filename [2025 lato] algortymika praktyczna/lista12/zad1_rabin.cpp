#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef unsigned long long ull;

int p = 61;
int mod = 1e9 + 9;
vector<ull> p_powers;
vector<ull> prefixes;

ull calculate_hash(string& s)
{
    ull hash = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        hash = (hash + (s[i] - 'a' + 1) * p_powers[i]) % mod;
    }
    return hash;
}

int rabin_karp(string& word, string& pattern)
{
    int pattern_len = pattern.size();
    ull pattern_hash = calculate_hash(pattern);
    int count = 0;

    for (int i = 0; i <= (int)word.size() - pattern_len; i++)
    {
        ull sub_hash = (prefixes[i + pattern_len] + mod - prefixes[i]) % mod;
        if (sub_hash == pattern_hash * p_powers[i] % mod)
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
    prefixes.resize(n + 1);

    p_powers[0] = 1;
    for (int i = 1; i < n; i++)
    {
        p_powers[i] = (p_powers[i - 1] * p) % mod;
    }
    prefixes[0] = 0;
    for (int i = 0; i < n; i++)
    {
        prefixes[i + 1] = (prefixes[i] + ((word[i] - 'a' + 1) * p_powers[i]) % mod) % mod;
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