#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> tree;
vector<vector<int>> up;
vector<int> time_in, time_out;

void preprocessing(int node, int parent, int &curr_time, int log_N)
{
    up[node][0] = parent;
    for (int i = 1; i <= log_N; i++)
    {
        up[node][i] = up[up[node][i - 1]][i - 1];
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

int find_lca(int u, int v, int log_N)
{
    if (time_in[u] <= time_in[v] && time_out[v] <= time_out[u]) return u;
    if (time_in[v] <= time_in[u] && time_out[u] <= time_out[v]) return v;

    // jump i = skok o 2^i wierzcholkow
    for (int jump = log_N; jump >= 0; jump--)
    {
        int new_u = up[u][jump];
        if (time_in[new_u] > time_in[v] || time_out[v] > time_out[new_u])
        {
            // new_u nie jest jeszcze lca wiec szukamy dalej
            u = new_u;
        }
    }
    // zwracamy rodzica u
    return up[u][0];
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    int log_N = ceil(log2(N));

    time_in.resize(N + 1);
    time_out.resize(N + 1);
    tree.resize(N + 1);
    up.resize(N + 1, vector<int>(log_N + 1));
    
    int parent, u, v;
    for (int node = 2; node <= N; node++)
    {
        cin >> parent;
        tree[parent].push_back(node);
        tree[node].push_back(parent);
    }

    int curr_time = 0;
    preprocessing(1, 1, curr_time, log_N);

    for (auto a : up)
    {
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < Q; i++)
    {
        cin >> u >> v;
        cout << find_lca(u, v, log_N) << '\n';
    }
    return 0;
}