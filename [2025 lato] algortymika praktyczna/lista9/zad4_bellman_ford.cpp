#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

typedef struct edge
{
    int source;
    int dest;
    ll weight;
} edge;

vector<edge> edges;
vector<ll> dist;
vector<int> ancestor;

// po i-tej iteracji wszystkie sciezki o dlugosci i sa optymalne
void bellman_ford(int N)
{
    dist[0] = 0;
    int last_changed;
    bool is_improved = false;
    for (int i = 0; i < N; i++)
    {
        last_changed = -1;
        for (edge e : edges)
        {
            if (dist[e.source] < INF &&  dist[e.dest] > dist[e.source] + e.weight)
            {
                dist[e.dest] = dist[e.source] + e.weight;
                ancestor[e.dest] = e.source;
                last_changed = e.dest;
                is_improved = true;
            }
        }
        if (!is_improved) break;
    }

    if (last_changed == -1) cout << "NO\n";
    else 
    {
        vector<int> path;
        int fst = last_changed;
        for (int i = 0; i < N; i++)
        {
            fst = ancestor[fst];
        }
        for (int curr = fst; path.size() < 1 || curr != fst; curr = ancestor[curr])
        {
            path.push_back(curr);
        }
        path.push_back(fst);
        cout << "YES\n";
        for (int i = path.size() - 1; i >=0; i--) cout << path[i] << " ";
    }
}

int main()
{
    int N, M, u, v; ll w;
    cin >> N >> M;

    dist.resize(N + 1, 0);
    ancestor.resize(N + 1, -1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    bellman_ford(N);
    return 0;
}