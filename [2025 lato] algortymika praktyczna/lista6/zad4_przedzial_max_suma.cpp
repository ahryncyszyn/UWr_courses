#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

typedef struct Node
{   
    long long sum;
    long long prefix;
    long long suffix;
    long long max_sum;
} tree_node;

vector<tree_node> tree;

void update_tree(int node, int left, int right, int idx, ll num)
{
    if (left == right)
    {
        tree[node].sum = num;
        tree[node].prefix = num;
        tree[node].suffix = num;
        tree[node].max_sum = num;
        return;
    }
    
    int mid = (left + right) / 2;
    if (idx <= mid) update_tree(2 * node, left, mid, idx, num);
    else update_tree(2 * node + 1, mid + 1, right, idx, num);

    tree_node left_child = tree[2 * node];
    tree_node right_child = tree[2 * node + 1];
    tree[node].sum = left_child.sum + right_child.sum;
    tree[node].prefix = max(left_child.prefix, left_child.sum + right_child.prefix);
    tree[node].suffix = max(right_child.suffix, right_child.sum + left_child.suffix);
    tree[node].max_sum = max(left_child.max_sum, max(right_child.max_sum, left_child.suffix + right_child.prefix));
}

int main()
{
    int N, Q; ll num;
    cin >> N >> Q;
    tree.resize(4 * N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        update_tree(1, 0, N - 1, i, num);
    }

    int idx; ll new_num;
    for (int i = 0; i < Q; i++)
    {
        cin >> idx >> new_num;
        update_tree(1, 0, N - 1, idx - 1, new_num);
        ll max_sum = max(0LL, tree[1].max_sum);
        cout << max_sum << "\n";
    }

    return 0;
}