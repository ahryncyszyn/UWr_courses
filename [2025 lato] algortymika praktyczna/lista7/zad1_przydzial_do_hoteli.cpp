#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> tree;

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
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

ll find_hotel_room(int node, int left, int right, ll people)
{
    if (left == right)
    {
        if (tree[node] < people) return -1;
        else return left;
    }

    int mid = (left + right) / 2;
    if (tree[2 * node] >= people) return find_hotel_room(2 * node, left, mid, people);
    else return find_hotel_room(2 * node + 1, mid + 1, right, people);
}

// zloz czas: O((N + Q) * log(N))
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;

    ll num;
    tree.resize(4 * N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        update_tree(1, 0, N - 1, i, num);
    }

    int hotel_room; ll people;
    for (int i = 0; i < Q; i++)
    {
        cin >> people;
        hotel_room = find_hotel_room(1, 0, N - 1, people);
        cout << hotel_room + 1 << " ";      // to account for 1-indexing
        if (hotel_room >= 0) update_tree(1, 0, N - 1, hotel_room, -people);
    }

}