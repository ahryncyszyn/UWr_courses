#include <iostream>
#include <vector>
using namespace std;

typedef struct mypair
{
    int max_matching_v_connected;
    int max_matching_v_free;
} mypair;

void find_max(int node, int parent, vector<vector<int>> &tree, vector<mypair> &dp, int N)
{
    // 
    int sum = 0;
    for (auto child : tree[node])
    {
        if (child == parent) continue;
        find_max(child, node, tree, dp, N);  
        sum += max(dp[child].max_matching_v_free, dp[child].max_matching_v_connected);  
    }
    dp[node].max_matching_v_connected = sum;
    dp[node].max_matching_v_free = sum;

    int best_matching_with = 0;
    for (auto child : tree[node])
    {
        if (child == parent) continue;
        int candidate = sum - max(dp[child].max_matching_v_free, dp[child].max_matching_v_connected)
                        + dp[child].max_matching_v_connected + 1;
        dp[node].max_matching_v_free = max(dp[child].max_matching_v_free, candidate);
    }
}

// skojarzenie - zbior krawedzi, z ktorych zadna nie laczy tych samych wierzcholkow
int main()
{
    int N;
    cin >> N;

    // wczytywanie drzewa
    vector<vector<int>> tree(N + 1, vector<int>());
    int a, b;
    for (int i = 1; i < N; i++)
    {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // będziemy dynamicznie zliczać maksymalny rozmiar zbioru
    // wierzchołkow gdy krawedz z rodzicem (danym v) jest uzyta lub nie
    vector<mypair> dp(N + 1);
    find_max(1, -1, tree, dp, N);

    // wynik to najwiekszy z dwoch zliczonych wersji
    cout << max(dp[1].max_matching_v_connected, dp[1].max_matching_v_free);
}
