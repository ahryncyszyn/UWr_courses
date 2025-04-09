#include <iostream>
#include <vector>
using namespace std;

void dfs(int v, vector<vector<int>> &graph, vector<int> &visited)
{
    visited[v] = 1;
    for (auto u : graph[v])
    {
        if (!visited[u])
        {
            dfs(u, graph, visited);
        }
    }
}

int main()
{
    int vertices_count, edges_count;
    cin >> vertices_count >> edges_count;

    vector<vector<int>> graph(vertices_count + 1);
    int v, u;
    for (int i = 0; i < edges_count; i++)
    {
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    vector<int> visited(vertices_count + 1);
    dfs(1, graph, visited);

    int to_build = 0;
    for (int v = 1; v <= vertices_count; v++)
    {
        if (!visited[v])
        {
            to_build++;
            dfs(v, graph, visited);
        }
    }

    cout << to_build << endl;
}