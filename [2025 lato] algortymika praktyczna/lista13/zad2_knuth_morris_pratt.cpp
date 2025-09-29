#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> lps;

void create_prefixsufix_table(string word)
{
    int M = word.size();
    lps.resize(M);
    lps[0] = 0;

    for (int i = 1; i < M; i++)
    {
        int prev_len = lps[i - 1];
        while (prev_len > 0 && word[i] != word[prev_len])
        {
            prev_len = lps[prev_len - 1];
        }
        if (word[i] == word[prev_len]) prev_len++;
        lps[i] = prev_len;
    }
}

int knuth_morris_pratt(string word, string pattern)
{
    string s = pattern + '#' + word;
    int pattern_len = pattern.size();
    int s_len = s.size();
    create_prefixsufix_table(s);
    int count = 0;
    for (int i = pattern_len + 1; i < s_len; i++)
    {
        // oznacza to ze dany fragment word jest rowny prefixowi s, czyli naszemu pattern
        if (lps[i] == pattern_len) count++;
    }
    return count;
}

int main()
{
    string word, pattern;
    cin >> word >> pattern;
    cout << knuth_morris_pratt(word, pattern);
}