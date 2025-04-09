#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 1000000
int repr[MAX_VERTICES + 1];
int set_size[MAX_VERTICES + 1];
int parity[MAX_VERTICES + 1];

struct repr_parity
{
    int repr;
    int parity;
};

void initalize_dsu(int N)
{
    // kazdy wierzcholek w osobnym zbiorze
    for (int i = 1; i <= N; ++i) 
    {
        repr[i] = i;
        set_size[i] = 1;
        parity[i] = 0;
    }
}

int find(int v)
{
    if (repr[v] == v)
    {
        return v;
    }
    return find(repr[v]);
}

bool unite(int a, int b, int p)
{
    int rootA = find(a);
    int rootB = find(b);

    // sa juz w jednym zbiorze
    if (rootA == rootB) return;

    // zapewnia ze bedziemy dolaczac mniejszy zbior do wiekszego
    if (set_size[rootA] < set_size[rootB])
    {
        swap(rootA, rootB);
    }

    repr[rootB] = rootA;
    set_size[rootA] += set_size[rootB];
}

int main()
{
    int N, M;
    cin >> N >> M;

    initalize_dsu(N);

    // sprawdzanie kolejnych punktow
    int a, b, p;
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> p;
        if (!unite(a, b, p))
        {
            cout << (i - 1);
            return 0;
        }
    }
}