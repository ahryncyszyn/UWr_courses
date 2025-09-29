#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<set<int>> graph; // trzyma krawedzie posortowane rosnaco
vector<int> indegree, outdegree;
vector<bool> visited;
vector<int> euler_cycle;

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
    // startowy wierzcholek musi miec wiecej krawedzi wychodzacych
    if (outdegree[1] != indegree[1] + 1) return 0;
    // koncowy wierzcholek musi miec wiecej krawedzi wchodzacych
    if (indegree[N] != outdegree[N] + 1) return 0;

    // pozostale wierzcholki musza miec tyle samo wchodzacych co wychodzacych
    for (int i = 2; i < N; i++)
    {
        if (indegree[i] != outdegree[i])
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
        dfs_euler(neigh);
    }
    euler_cycle.push_back(node);
}

int main()
{
    int N, M, u, v;
    cin >> N >> M;
    indegree.resize(N + 1, 0);
    outdegree.resize(N + 1, 0);
    graph.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].insert(v);
        outdegree[u]++; 
        indegree[v]++;
    }

    if (!is_eulerian(N))
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    dfs_euler(1);
    reverse(euler_cycle.begin(), euler_cycle.end());
    for (int node : euler_cycle) cout << node << " ";
    return 0;
}