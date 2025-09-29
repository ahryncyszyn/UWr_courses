#include <iostream>
#include <vector>
#include <set>
using namespace std;
vector<set<int>> graph;
vector<int> euler_cycle;
vector<int> indegree;
vector<bool> visited;

// sciezka eulera - sciezka ktora odwiedza kazdy wierzcholek dokładnie raz
// cykl eulera - sciezka eulera ktora zaczyna i konczy sie w tym samym wierzcholku 

void dfs(int node)
{
    if (visited[node]) return;
    visited[node] = true;

    for (int neigh : graph[node])
    {
        dfs(neigh);
    }
}

int is_eulerian(int N)
{
    // kazdy wierzcholek musi miec parzysty stopien
    for (int i = 1; i <= N; i++)
    {
        if (indegree[i] % 2 != 0)
        {
            return 0;
        }
    }

    // graf musi byc spojny (poza wierzcholkami bez zadnych krawedzi)
    visited.assign(N + 1, false);
    dfs(1);
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i] && indegree[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}

// przejscie post-order
void dfs_euler(int node)
{
    while (!graph[node].empty())
    {
        int neigh = *graph[node].begin();
        graph[node].erase(neigh);
        graph[neigh].erase(node);
        dfs_euler(neigh);
    }
    euler_cycle.push_back(node);
}

int main()
{
    int N, M, u, v;
    cin >> N >> M;
    indegree.resize(N + 1, 0);
    graph.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
        indegree[u]++; indegree[v]++;
    }

    if (!is_eulerian(N))
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    dfs_euler(1);
    for (auto node : euler_cycle) cout << node << " ";
    return 0;
}