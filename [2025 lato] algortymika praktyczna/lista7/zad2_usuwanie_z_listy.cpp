#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
vector<ll> tree;

// num to 1 lub -1 w zaleznosci czy dodajemy liczbe do tablicy czy usuwamy
void update_tree(int node, int left, int right, int idx, ll num)
{
    if (left == right)
    {
        tree[node] += num;
        return;
    }

    int mid = (left + right) / 2;
    if (idx <= mid) update_tree(2 * node, left, mid, idx, num);
    else update_tree(2 * node + 1, mid + 1, right, idx, num);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

ll find_kth_num(int node, int left, int right, int idx)
{
    if (left == right) return left;

    int mid = (left + right) / 2;
    if (idx <= tree[2 * node]) return find_kth_num(2 * node, left, mid, idx);
    else return find_kth_num(2 * node + 1, mid + 1, right, idx - tree[2 * node]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, idx;
    cin >> N;

    tree.resize(4 * N);
    vector<ll> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
        update_tree(1, 0, N - 1, i, 1);
    }

    for (int i = 0; i < N; i++)
    {
        cin >> idx;
        int original_idx = find_kth_num(1, 0, N - 1, idx);
        cout << nums[original_idx] << " ";
        update_tree(1, 0, N - 1, original_idx, -1);
    }
}