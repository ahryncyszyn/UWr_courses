#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

typedef struct Node
{
    long long sum;
    long long max_prefix;
} tree_node;

vector<tree_node> tree;

void update_tree(int node, int left, int right, int idx, ll new_value)
{
    if (left == right)
    {
        tree[node].sum = new_value;
        tree[node].max_prefix = new_value;
        return;
    }
    int mid = (left + right) / 2;
    if (idx <= mid) update_tree(2 * node, left, mid, idx, new_value);
    else update_tree(2 * node + 1, mid + 1, right, idx, new_value);

    tree_node left_child = tree[2 * node];
    tree_node right_child = tree[2 * node + 1];
    tree[node].sum = left_child.sum + right_child.sum;
    tree[node].max_prefix = max(left_child.max_prefix, left_child.sum + right_child.max_prefix);
}

tree_node find_max_prefix(int node, int left, int right, int query_left, int query_right)
{
    if (query_right < left || right < query_left) return {0, 0};
    if (query_left <= left && right <= query_right) return tree[node];

    int mid = (left + right) / 2;
    tree_node left_result = find_max_prefix(2 * node, left, mid, query_left, query_right);
    tree_node right_result = find_max_prefix(2 * node + 1, mid + 1, right, query_left, query_right);

    tree_node res;
    res.sum = left_result.sum + right_result.sum;
    res.max_prefix = max(left_result.max_prefix, left_result.sum + right_result.max_prefix);
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, q, idx, new_value, x, y;
    cin >> N >> Q;

    long long num;
    tree.resize(4 * N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        update_tree(1, 0, N - 1, i, num);
    }

    for (int i = 0; i < Q; i++)
    {
        cin >> q;
        if (q == 1)
        {
            cin >> idx >> new_value;
            update_tree(1, 0, N - 1, idx - 1, new_value);
        }
        else if (q == 2)
        {
            cin >> x >> y;
            ll max_prefix = find_max_prefix(1, 0, N - 1, x - 1, y - 1).max_prefix;
            max_prefix = max(max_prefix, 0LL);
            cout << max_prefix << "\n";
        }
    }
    return 0;
}

