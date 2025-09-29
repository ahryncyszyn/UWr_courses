#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

typedef struct node
{
    ll val;
    vector<int> neighbours;
} node;

vector<node> tree;
vector<int> time_in;
vector<int> time_out;
vector<int> euler_tour;
vector<ll> vals_tour;
vector<ll> segment_tree;

void euler(int node, int parent)
{
    time_in[node] = euler_tour.size();
    euler_tour.push_back(node);
    vals_tour.push_back(tree[node].val);

    for (int child : tree[node].neighbours)
    {
        if (child != parent)
        {
            euler(child, node);
        }
    }
    euler_tour.push_back(node);
    vals_tour.push_back(-tree[node].val);
    time_out[node] = euler_tour.size() - 1;
}

void update_segment_tree(int node, int left, int right, int idx, ll new_val)
{
    if (left == right)
    {
        segment_tree[node] = new_val;
        return;
    }

    int mid = (left + right) / 2;
    if (idx <= mid) update_segment_tree(2 * node, left, mid, idx, new_val);
    else update_segment_tree(2 * node + 1, mid + 1, right, idx, new_val);
    segment_tree[node] = segment_tree[2 * node] + segment_tree[2 * node + 1];
}

ll calculate_subtree_sum(int node, int left, int right, int start, int end)
{
    if (end < left || right < start) return 0;
    if (start <= left && right <= end) return segment_tree[node];

    int mid = (left + right) / 2;
    return calculate_subtree_sum(2 * node, left, mid, start, end) 
         + calculate_subtree_sum(2 * node + 1, mid + 1, right, start, end);
}

int main()
{
    int N, Q, u, v, q; ll x;
    cin >> N >> Q;

    tree.resize(N + 1);
    segment_tree.resize(4 * 2 * N);
    time_in.resize(N + 1);
    time_out.resize(N + 1);
    for (int i = 1; i <= N; i++)
    {   
        cin >> tree[i].val;
    }
    for (int i = 1; i < N; i++)
    {
        cin >> u >> v;
        tree[u].neighbours.push_back(v);
        tree[v].neighbours.push_back(u);
    }

    euler(1, 1);
    int euler_size = euler_tour.size();
    for (int i = 0; i < euler_size; i++)
    {
        update_segment_tree(1, 0, euler_size - 1, i, vals_tour[i]);
    }
    
    for (int i = 0; i < Q; i++)
    {   
        cin >> q >> v;
        if (q == 1)
        {
            cin >> x;
            update_segment_tree(1, 0, euler_size - 1, time_in[v], x);
            update_segment_tree(1, 0, euler_size - 1, time_out[v], -x);

        }
        if (q == 2)
        {
            cout << calculate_subtree_sum(1, 0, euler_size - 1, 0, time_in[v]) << "\n";
        }
    }
}