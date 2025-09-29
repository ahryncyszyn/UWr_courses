#include <iostream>
#include <vector>
using namespace std;

vector<int> tree;
long long inversions = 0;

// dodaje liczbe num do drzewa przedzialowego
// drzewo zlicza wystepowania danych liczb
void update_values(int node, int num, int left, int right)
{
    if (left == right)
    {
        tree[node]++;
        return;
    }

    int mid = (left + right) / 2;
    if (num <= mid) update_values(2 * node, num, left, mid);
    else update_values((2 * node) + 1, num, mid + 1, right);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int left, int right, int query_left, int query_right)
{
    if (query_right < left || right < query_left) return 0;
    if (query_left <= left && right <= query_right) return tree[node];

    int mid = (left + right) / 2;
    return query(2 * node, left, mid, query_left, query_right) +
           query(2 * node + 1, mid + 1, right, query_left, query_right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, max_num = 0;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
        max_num = max(max_num, nums[i]);
    }
    
    tree.resize(4 * max_num, 0);
    for (int i = 0; i < N; i++)
    {
        update_values(1, nums[i], 0, max_num);
        if (nums[i] != max_num)
        {
            inversions += query(1, 0, max_num, nums[i] + 1, max_num);
        }
    }
    cout << inversions;
    return 0;
}