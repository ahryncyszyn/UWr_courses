#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> tree;
vector<vector<int>> up;

void preprocessing(int node, int parent, int log_N)
{
    up[node][0] = parent;
    for (int i = 1; i <= log_N; i++)
    {
        int prev = up[node][i - 1];
        if (prev != -1) up[node][i] = up[prev][i - 1];
        else up[node][i] = -1;
    }

    for (int child : tree[node])
    {
        if (child != parent)
        {
            preprocessing(child, node, log_N);
        }
    }
}

int find_ancestor(int node, int k, int log_N)
{
    for (int i = 0; i <= log_N; i++)
    {
        if (node == -1) return -1;
        if (k & (1 << i))
        {
            node = up[node][i];
        }
    }
    return node;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    int log_N = ceil(log2(N));

    tree.resize(N + 1);
    up.resize(N + 1, vector<int>(log_N + 1, -1));
    
    int parent, k, node;
    for (int node = 2; node <= N; node++)
    {
        cin >> parent;
        tree[parent].push_back(node);
        tree[node].push_back(parent);
    }

    preprocessing(1, -1, log_N);

    for (int i = 0; i < Q; i++)
    {
        cin >> node >> k;
        cout << find_ancestor(node, k, log_N) << '\n';
    }
    return 0;
}