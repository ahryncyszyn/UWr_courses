#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void find_distances(int vertices_count, vector<vector<int>> &graph)
{
    vector<int> distances(vertices_count + 1, -1);
    distances[1] = 0;

    queue<int> queue;
    queue.push(1);

    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();

        for (auto neighbour : graph[v])
        {
            if (distances[neighbour] == -1)
            {
                distances[neighbour] = distances[v] + 1;
                queue.push(neighbour);
            }
        }
    }

    for (int i = 2; i <= vertices_count; i++)
    {
        cout << distances[i] << " ";
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

    find_distances(vertices_count, graph);
}