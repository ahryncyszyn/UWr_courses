#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

const int MAXN = 200000;
vector<int> tree[MAXN + 1];
int colors[MAXN + 1];
unordered_set<int> color_sets[MAXN + 1];

void dfs(int v, int parent)
{
    cout << v << " " << parent << endl;
    int max_set_node = -1;
    for (int u : tree[v])
    {
        if (u == parent) continue;
        dfs(u, v);
        if (max_set_node == -1 || color_sets[u].size() > color_sets[max_set_node].size())
        {
            max_set_node = u;
        }
    }
    cout << v << " " << parent << endl;

    if (max_set_node != -1) swap(color_sets[v], color_sets[max_set_node]);

    // dodajemy kolory z mniejszych poddrzew do `color_sets[v]`
    for (int u : tree[v]) 
    {
        if (u == parent || u == max_set_node) continue;
        for (int color : color_sets[u]) 
        {
            color_sets[v].insert(color);
        }
    }

    // Dodajemy własny kolor wierzchołka
    color_sets[v].insert(colors[v]);
    cout << v << " " << parent << endl;
}

int main()
{
    cout.tie(0); cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N; // liczba wierzchołkow drzewa
    cin >> N;

    // wczytywanie kolorow drzew
    for (int i = 1; i <= N; i++)
    {
        cin >> colors[i];
    }

    // wczytywanie struktury drzewa - lista sasiedztwa
    int a, b;
    for (int i = 1; i < N; i++)
    {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    } 

    dfs(1, -1);
    for (int i = 1; i <= N; i++)
    {
        cout << color_sets[i].size() << " ";
    }

    return 0;
}