#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

vector<ll> tree;

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
long long query(int i)
{
    long long res = 0;
    while (i > 0)
    {
        res += tree[i];
        i /= 2;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, q, idx, x, y;
    long long incr;
    cin >> N >> Q;

    tree.resize(4 * N, 0);
    int start = 1 << static_cast<int>(ceil(log2(N)));
    for (int i = 0; i < N; i++)
    {
        cin >> tree[start + i];
    }

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
            cout << query(start + idx - 1) << '\n';
        } 
    }
    return 0;
}