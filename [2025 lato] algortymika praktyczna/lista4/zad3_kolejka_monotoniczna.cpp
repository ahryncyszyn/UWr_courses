
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // wczytywanie tablicy liczb
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // sortowanie zapytan na podstawie konca zakresu
    int a, b;
    vector<vector<pair<int, int>>> queries(N);
    for (int i = 0; i < Q; i++)
    {
        cin >> a >> b;
        a--; b--;
        queries[b].push_back({a, i});
    }   

    // wyznaczanie minimow jednym przejsciem przez liczby
    deque<pair<int, int>> q;
    vector<int> results(Q);
    for (int i = 0; i < N; i++)
    {
        // tworzenie kolejki tak zeby miec w niej mimalne liczby i indeks od kiedy sie zaczynaja (a)
        // np dla nums = [3, 2, 4]
        // dla i = 1 wyrzucamy 3 z kolejki bo wiemy ze zawsze ten zakres ma mniejsza liczbe (2)
        // dla i = 2 zostawiamy zarowno 2 i 4, bo w zaleznosci od a minimum moze byc rozne
        while (!q.empty() && q.back().first >= nums[i]) 
        {
            q.pop_back();
        }
        q.push_back({nums[i], i});

        // odpowiadanie na zapytania
        for (auto [a, idx] : queries[i]) 
        {   
            // znajduje wiekszy lub rowny indeks od a, pod nim jest minimalny element zakresu
            auto lb = lower_bound(q.begin(), q.end(), a, 
                      [](const pair<int, int>& p, int value){return p.second < value;});
            results[idx] = lb->first;
        }
    }

    for (int i = 0; i < Q; i++)
    {
        cout << results[i] << '\n';
    }
    return 0;
}