#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// dowod ze jezeli algorytm sie zatnie to istnieje cykl
// skoro algorytm sie zacial to znaczy ze wszsytkie wiecholki maja jakiegos rodzica
// bierzemy wierzcholek x, wiec wiemy ze ma on rodzica
// cofamy sie do rodzica rodzica i tak dalej N razy, wiec wtedy wrocimy do wierzcholka x
// czyli był cykl w grafie

vector<vector<int>> graph;
priority_queue<int, vector<int>, greater<int>> nodes_queue;
vector<int> in_degree;
vector<int> sccs_sorted;

void topological_sort(int N)
{
    for (int i = 1; i <= N; i++)
    {   
        if (in_degree[i] == 0) nodes_queue.push(i); 
    }

    while (!nodes_queue.empty())
    {   
        int node = nodes_queue.top();
        nodes_queue.pop();
        sccs_sorted.push_back(node);

        for (int neighb : graph[node])
        {
            in_degree[neighb]--;

            if (in_degree[neighb] == 0)
            {
                nodes_queue.push(neighb);

            }
        }
    }

    if (sccs_sorted.size() != static_cast<std::size_t>(N))
    {
        cout << "IMPOSSIBLE";
    }
    else for (int n : sccs_sorted) cout << n << " ";
}

int main()
{
    int N, M, u, v;
    cin >> N >> M;

    graph.resize(N + 1);
    in_degree.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        in_degree[v]++;
    }

    topological_sort(N);

    return 0;
}