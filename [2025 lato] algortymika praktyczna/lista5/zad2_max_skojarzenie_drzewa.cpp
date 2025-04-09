#include <iostream>
#include <vector>
using namespace std;

vector<int> visited;

void find_max(int node, vector<vector<int>> &tree, vector<pair<int, int>> &dp, int N)
{
    if (visited[node]) return;
    visited[node] = 1;

    int max_assoc = 0;
    int max_height1 = -1;
    vector<int> sub_graph;
    for (auto child : tree[node])
    {
        if (visited[child]) continue;
        find_max(child, tree, dp, N);  
        
        //matching_withou[start] += best_matching[i]
        // sub_graph.pushback(child)        
    }

    int best_matching_with = 0;
    for (auto i : sub_graph)
    {
        // best_matching_with = max(best_matching_with, matching_without[start])
    }
    // wyznaczanie maksymalnej srednicy dla danego wierzcholka

}

// skojarzenie - zbior krawedzi, z ktorych zadne nie laczy tych samych wierzcholkow
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

    // przechowuje dla kazdego wierzcholka pare
    // (max_skojarzenie, max_skojarzenie_bez_korzenia)
    vector<pair<int, int>> dp(N+1);
    visited.assign(N+1, 0);
    find_max(1, tree, dp, N);

    // wypisywanie maksymalnej srednicy drzewa (przechowywana w korzeniu)
    cout << max(dp[1].first, dp[1].second);
}
