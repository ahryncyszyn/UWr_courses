#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> tree;

void build_tree(int node, vector<ll> &nums, int left, int right)
{
    if (left == right)
    {
        tree[node] = nums[left];
        return;
    }
    int mid = (left + right) / 2;
    build_tree(2 * node, nums, left, mid);
    build_tree(2 * node + 1, nums, mid + 1, right);
    tree[node] = 0;
}

// zapisuje w drzewie o ile zostaly zwiekszone oryginalne wartosci na przedziale danego wierzcholka
void update_tree(int node, int left, int right, int range_left, int range_right, ll incr)
{
    if (range_right < left || right < range_left) return;
    if (range_left <= left && right <= range_right)
    {
        tree[node] += incr;
        return;
    }
    int mid = (left + right) / 2;
    update_tree(2 * node, left, mid, range_left, range_right, incr);
    update_tree(2 * node + 1, mid + 1, right, range_left, range_right, incr);
}

// przechodzi od lisci do korzenia, sumujac wartosci
ll query(int node, int left, int right, int query_left, int query_right, ll res)
{
    if (left == right)
    {
        return tree[node] + res;
    }

    int mid = (left + right) / 2;
    if (query_left <= mid) return query(2 * node, left, mid, query_left, query_right, res + tree[node]);
    else return query(2 * node + 1, mid + 1, right, query_left, query_right, res + tree[node]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, q, idx, x, y;
    long long incr;
    cin >> N >> Q;

    tree.resize(4 * N, 0);
    vector<ll> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
    build_tree(1, nums, 0, N - 1);

    for (int i = 0; i < Q; i++)
    {
        cin >> q;
        if (q == 1)
        {
            cin >> x >> y >> incr;
            update_tree(1, 1, N, x, y, incr);
        }
        else if (q == 2)
        {
            cin >> idx;
            cout << query(1, 0, N - 1, idx - 1, N - 1, 0) << endl;
        } 
    }
    return 0;
}