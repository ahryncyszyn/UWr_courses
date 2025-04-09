#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 100000
int repr[MAX_VERTICES + 1];
int edges_count[MAX_VERTICES + 1];
int min_vertex[MAX_VERTICES + 1];
int max_vertex[MAX_VERTICES + 1];

int find(int v)
{
    if (repr[v] != v)
    {
        // kompresja sciezki
        repr[v] = find(repr[v]);
    }
    return repr[v];
}

void unite(int u, int v)
{
    int rootU = find(u);
    int rootV = find(v);

    // sa juz w jednym zbiorze
    if (rootU == rootV)
    {
        edges_count[rootU]++;
        return;
    }

    // zapewnia ze bedziemy dolaczac mniejszy zbior do wiekszego
    if (edges_count[rootU] < edges_count[rootV])
    {
        swap(rootU, rootV);
    }

    repr[rootV] = rootU;
    edges_count[rootU] += edges_count[rootV] + 1;
    min_vertex[rootU] = min(min_vertex[rootU], min_vertex[rootV]);
    max_vertex[rootU] = max(max_vertex[rootU], max_vertex[rootV]);
}

int main()
{
    int N, M;
    cin >> N >> M;

    // inicjowanie - kazdy wierzcholek w osobnym zbiorze
    for (int i = 1; i <= N; ++i) 
    {
        repr[i] = i;
        edges_count[i] = 0;
        min_vertex[i] = i;
        max_vertex[i] = i;
    }

    // laczenie zbiorow
    int u, v;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        unite(u, v);
        cout << (long long)(max_vertex[find(u)] - min_vertex[find(u)]) * edges_count[find(u)] << "\n";
    }
}