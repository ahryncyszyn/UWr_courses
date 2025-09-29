
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

vector<vector<ll>> dst;

// ujemny cykl kiedy dist[v][v] < 0
// niezmiennik - po k-tym kroku d[i][j] zawiera dlugosc najkrotszej scieki i -> j
// ktora ma wierzcholki posrednie ze zbioru {1, ... k - 1}
void floyd_warshall(int N)
{
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dst[i][k] < INF && dst[k][j] < INF)
                {
                    dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
                }
            }
        }
    }
}

int main()
{
    int N, M, Q, u, v; ll weight;
    cin >> N >> M >> Q;

    dst.resize(N + 1, vector<ll>(N + 1, INF));
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> weight;
        dst[u][v] = min(dst[u][v], weight);
        dst[v][u] = min(dst[v][u], weight);
    }
    for (int i = 1; i <= N; i++) dst[i][i] = 0;

    floyd_warshall(N);

    for (int i = 0; i < Q; i++)
    {
        cin >> u >> v;
        if (dst[u][v] == INF) cout << "-1\n"; 
        else cout << dst[u][v] << "\n";
    }
    return 0;
}