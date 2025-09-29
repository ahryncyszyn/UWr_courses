#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> paths;        // na zliczanie zmian przez dodane sciezki
vector<int> sccs_sorted;  // na wynik - liczba sciezek przechodzacych przez dany wierzcholek

vector<int> time_in;      // na czas wejscia do wierzcholka
vector<int> time_out;     // na czas wyjscia z wierzcholka
vector<vector<int>> up;   // na przechodkow do binary lifting
vector<vector<int>> tree; 

void preprocessing(int node, int parent, int &curr_time, int log_N)
{
    up[node][0] = parent;
    for (int i = 1; i <= log_N; i++)
    {
        int prev = up[node][i - 1];
        if (prev != -1) up[node][i] = up[prev][i - 1];
        else up[node][i] = -1;
    }
    
    time_in[node] = ++curr_time;
    for (int child : tree[node])
    {
        if (child != parent)
        {
            preprocessing(child, node, curr_time, log_N);
        }
    }
    time_out[node] = ++curr_time;
}

int is_ancestor(int u, int v) 
{
    return time_in[u] <= time_in[v] && time_out[u] >= time_out[v];
}

int find_lca(int u, int v, int log_N)
{
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int jump = log_N; jump >= 0; jump--)
    {
        // jezeli nowe u jest przodkiem v to znaczy ze skoczylismy za wysoko
        // wpp u = nowe_u az dojdziemy do ostatniego wierzcholka ktory nie jest przodkiem v
        // wtedy jego rodzic jest lca(u, v)
        if (up[u][jump] != -1 && !(is_ancestor(up[u][jump], v)))
        {
            u = up[u][jump];
        }
    }
    return up[u][0];
}

int calculate_results(int node, int parent)
{
    int res = paths[node];
    for (int child : tree[node])
    {
        if (child != parent)
        {
            res += calculate_results(child, node);
        } 
    }
    sccs_sorted[node] = res;
    return res;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    int log_N = ceil(log2(N));

    paths.resize(N + 1);
    sccs_sorted.resize(N + 1);
    time_in.resize(N + 1);
    time_out.resize(N + 1);
    up.resize(N + 1, vector<int>(log_N + 1, -1));
    tree.resize(N + 1);

    int u, v;
    for (int i = 1; i < N; i++)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    int curr_time = 0, lca;
    preprocessing(1, -1, curr_time, log_N);

    for (int i = 0; i < Q; i++)
    {
        cin >> u >> v;
        paths[u]++;
        paths[v]++;
        lca = find_lca(u, v, log_N);
        paths[lca]--;
        if (up[lca][0] != lca && up[lca][0] != -1) paths[up[lca][0]]--;
    }
    
    calculate_results(1, 1);
    for (int i = 1; i <= N; i++)
    {
        cout << sccs_sorted[i] << " ";
    }
    return 0;
}