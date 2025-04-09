#include <iostream>
#include <vector>
using namespace std;

vector<int> visited;

void find_max(int node, vector<vector<int>> &tree, vector<pair<int, int>> &dp, int N)
{
    if (visited[node]) return;
    visited[node] = 1;

    int max_diam = 0;
    int max_height1 = -1, max_height2 = -1;
    for (auto child : tree[node])
    {
        if (visited[child]) continue;
        find_max(child, tree, dp, N);  
        
        // wyznaczanie maksymalnych wysokosci poddrzew
        int child_height = dp[child].second;
        if (child_height > max_height1)
        {
            max_height2 = max_height1;
            max_height1 = child_height;
        } else if (child_height > max_height2)
        {
            max_height2 = child_height;
        }
  
        // wyznczanie maksymalnej srednicy poddrzew
        max_diam = max(max_diam, dp[child].first);        
    }

    // wyznaczanie maksymalnej srednicy dla danego wierzcholka
    max_diam = max(max_diam, (max_height1 + max_height2 + 2));
    dp[node] = pair<int, int>(max_diam, max_height1 + 1);
}

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
    // (max_srednica_poddrzewa, wysokość poddrzewa)
    vector<pair<int, int>> dp(N+1);
    visited.assign(N+1, 0);
    find_max(1, tree, dp, N);

    // wypisywanie maksymalnej srednicy drzewa (przechowywana w korzeniu)
    cout << dp[1].first;
}
