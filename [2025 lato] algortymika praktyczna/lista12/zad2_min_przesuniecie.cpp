#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int p = 61;
int mod = 1e9 + 9;

vector<ll> p_powers;
vector<ll> hashes;

// zduplikowanie slowa i sklejenie
// hashe prefixowe
// H[b] - H[a] * p_power[b - a]
// zeby porownywac robimy binsearcha
// szukamy pierwszej literki gdzie nasze podslowa sie roznia
// gdy znajdziemy pierwsza literke na ktorej sie roznica to porownujemy

string find_min_word(string& word)
{
}

void preprocessing(string& word)
{
    int n = word.size();
    p_powers.resize(n);
    hashes.resize(n);

}

int main()
{
    string word;
    cin >> word;
    word += word;
    cout << find_min_word(word);
}