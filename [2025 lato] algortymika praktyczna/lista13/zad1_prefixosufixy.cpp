#include <iostream>
#include <vector>
#include <string>
using namespace std;

// tablica longest prefix suffix
vector<int> lps;

// dlaczego złozoność O(n)?
// wartosc lps[0] = 0, a potem
// w kazdej iteracji wartosc lps[i] wzrasta maksymalnie o 1 w porownaniu do poprzedniej
// najmniejsza wartosc prev_count to 0
// wiec w sumie petla while zostanie wykonana maksymalnie n razy przez cale wykonanie programu
// w sumie funkcja ma O(2 * n), gdzie n = word.size()
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

int main()
{
    string word;
    cin >> word;
    create_prefixsufix_table(word);

    vector<int> results;
    // wyliczenie najdluszego prefixosufixu calego slowa
    int res = lps[word.size() - 1];
    while (res > 0) 
    {
        results.push_back(res);
        // wyliczanie kolejnych prefixosufixow znalezionego prefixosufixu
        res = lps[res - 1];
    }
    reverse(results.begin(), results.end());
    for (int x : results) cout << x << " ";
}