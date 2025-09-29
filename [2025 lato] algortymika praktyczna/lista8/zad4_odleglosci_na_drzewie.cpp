
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<vector<int>> tree;
vector<int> segment_tree;
vector<int> depth_tour;
vector<int> euler_tour;
vector<int> first_occurence;

void euler(int node, int parent, int depth)
{
    first_occurence[node] = euler_tour.size();
    euler_tour.push_back(node);
    depth_tour.push_back(depth);

    for (int child : tree[node])
    {
        if (child != parent)
        {
            euler(child, node, depth + 1);
            euler_tour.push_back(node);
            depth_tour.push_back(depth);
        }
    }
}

void update_segment_tree(int node, int left, int right, int idx, int depth)
{
    if (left == right)
    {
        segment_tree[node] = depth;
        return;
    }

    int mid = (left + right) / 2;
    if (idx <= mid) update_segment_tree(2 * node, left, mid, idx, depth);
    else update_segment_tree(2 * node + 1, mid + 1, right, idx, depth);
    segment_tree[node] = min(segment_tree[2 * node], segment_tree[2 * node + 1]);
}

// znajduje najmniejsza glebokosc miedzy pierwszymi wystapieniami u i v w euler tour
int find_lca_depth(int node, int left, int right, int start, int end)
{
    if (end < left || right < start) return INT_MAX;
    if (start <= left && right <= end) return segment_tree[node];

    int mid = (left + right) / 2;
    return min(find_lca_depth(2 * node, left, mid, start, end), 
               find_lca_depth(2 * node + 1, mid + 1, right, start, end));
}

int main()
{
    int N, Q;
    cin >> N >> Q;

    tree.resize(N + 1);
    segment_tree.resize(4 * 2 * N);
    first_occurence.resize(N + 1);

    int u, v;
    for (int i = 1; i < N; i++)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    euler(1, 1, 1);
    int euler_size = euler_tour.size();
    for (int i = 0; i < euler_size; i++)
    {
        update_segment_tree(1, 0, euler_size - 1, i, depth_tour[i]);
    }

    // odleglosc = glebokosc(u) + glebokosc(v) - 2 * glebokosc(LCA(u,v)).
    for (int i = 0; i < Q; i++)
    {
        cin >> u >> v;
        int start = first_occurence[u];
        int end = first_occurence[v];
        if (start > end) swap(start, end);

        int lca_depth = find_lca_depth(1, 0, euler_size - 1, start, end);
        cout << depth_tour[start] + depth_tour[end] - 2 * lca_depth << "\n";
    }
}