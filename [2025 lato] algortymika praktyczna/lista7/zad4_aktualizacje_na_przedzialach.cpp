#include <iostream>
#include <vector>
using namespace std;

vector<int> tree, lazy;

void update_tree(int node, int left, int right, int x, int y, int diff)
{
    if (y < left || right < x) return;
    if (left == right)
    {
        tree[node] += diff;
        return;
    }

    int mid = (left + right) / 2;
    update_tree(2 * node, left, mid, x, y, diff);
    update_tree(2 * node + 1, mid + 1, right, x, y, diff);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void set_values(int node, int left, int right, int x, int y, int val)
{
    if (y < left || right < x) return;
    if (left == right)
    {
        tree[node] = val;
        return;
    }
    int mid = (left + right) / 2;
    set_values(2 * node, left, mid, x, y, val);
    set_values(2 * node + 1, mid + 1, right, x, y, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long count_sum(int node, int left, int right, int x, int y)
{
    if (y < left || right < x) return 0;
    if (left == right) return tree[node];

    int mid = (left + right) / 2;
    return count_sum(2 * node, left, mid, x, y) + 
           count_sum(2 * node + 1, mid + 1, right, x, y);
}

int main()
{
    int N, Q, q, x, y, v;
    cin >> N >> Q;

    int num;
    tree.resize(4 * N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        update_tree(1, 0, N - 1, i, i, num);
    }

    for (int i = 0; i < Q; i++)
    {
        for (auto t : tree)
        {
            cout << t << " ";
        }
        cout << endl;
        
        cin >> q >> x >> y;
        x--; y--;
        if (q == 1)
        {
            cin >> v;
            update_tree(1, 0, N - 1, x, y, v);
        }

        else if (q == 2)
        {
            cin >> v;
            set_values(1, 0, N - 1, x, y, v);
        }

        else if (q == 3)
        {
            cout << count_sum(1, 0, N - 1, x, y) << "\n";
        }
    }
    return 0;
}