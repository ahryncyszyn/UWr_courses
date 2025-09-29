#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef struct edge
{
    int dest;
    ll weight;
} edge;

typedef struct heap_node
{
    int node;
    ll dist;
} heap_node;

vector<vector<edge>> graph;
vector<ll> shortest_path;
vector<bool> visited;

bool compare(const heap_node& a, const heap_node& b) {
    return a.dist > b.dist;
}

void dijkstra(int start)
{
    shortest_path[start] = 0;
    vector<heap_node> heap;
    heap.push_back({start, 0});
    push_heap(heap.begin(), heap.end(), compare);

    while (!heap.empty())
    {
        cout << "heap is " << endl;
        for (auto h : heap) cout << "(" << h.node << ", " << h.dist << "), ";
        cout << endl;
        
        pop_heap(heap.begin(), heap.end(), compare);
        heap_node curr = heap.back();
        heap.pop_back();

        if (visited[curr.node]) continue;
        visited[curr.node] = true;

        for (edge e : graph[curr.node])
        {
            ll new_dist = shortest_path[curr.node] + e.weight;
            if (new_dist < shortest_path[e.dest])
            {
                shortest_path[e.dest] = new_dist;
                heap.push_back({e.dest, new_dist});
                push_heap(heap.begin(), heap.end(), compare);
            }
        }
    }
}

int main()
{
    int N, M, u, v; ll weight;
    cin >> N >> M;
    shortest_path.resize(2 * N + 1, LLONG_MAX);
    visited.resize(2 * N + 1, false);

    graph.resize(2 * N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
	    graph[u].push_back({v + N, (weight/2)});
        graph[u + N].push_back({v + N, weight});
    }

    dijkstra(1);

    cout << min(shortest_path[N], shortest_path[2 * N]);
}





