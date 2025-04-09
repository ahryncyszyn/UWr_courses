#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 100000
int repr[MAX_VERTICES + 1];
int set_size[MAX_VERTICES + 1];
int components_count;
int max_component_size;

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
    if (rootU == rootV) return;

    // zapewnia ze bedziemy dolaczac mniejszy zbior do wiekszego
    if (set_size[rootU] < set_size[rootV])
    {
        swap(rootU, rootV);
    }

    repr[rootV] = rootU;
    set_size[rootU] += set_size[rootV];
    max_component_size = max(set_size[rootU], max_component_size);
    components_count--;
}

int main()
{
    int N, M;
    cin >> N >> M;

    // inicjowanie - kazdy wierzcholek w osobnym zbiorze
    components_count = N;
    max_component_size = 1;
    for (int i = 1; i <= N; ++i) 
    {
        repr[i] = i;
        set_size[i] = 1;
    }

    // laczenie zbiorow
    int u, v;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        unite(u, v);
        cout << components_count << " " << max_component_size << "\n";
    }
}