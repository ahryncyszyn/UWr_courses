#include <iostream>
#include <vector> 
using namespace std;

vector<int> tree;

void build_tree(int node, int left, int right, int seats)
{
    if (left == right)
    {
        tree[node] = seats;
        return;
    }

    int mid = (left + right) / 2;
    build_tree(2 * node, left, mid, seats);
    build_tree(2 * node + 1, mid + 1, right, seats);
    tree[node] = seats;
}

void update_tree(int node, int left, int right, int start, int end, int people)
{
    if (end < left || right < start) return;
    if (left == right)
    {
        tree[node] -= people;
        return;
    }

    int mid = (left + right) / 2;
    update_tree(2 * node, left, mid, start, end, people);
    update_tree(2 * node + 1, mid + 1, right, start, end, people);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int is_available(int node, int left, int right, int start, int end, int people)
{
    if (end < left || right < start) return 1;
    if (start <= left && right <= end)
    {
        return (tree[node] >= people);
    }
    int mid = (left + right) / 2;
    return is_available(2 * node, left, mid, start, end, people) &&
           is_available(2 * node + 1, mid + 1, right, start, end, people);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cities_count, seats_count, queries_count;
    cin >> cities_count >> seats_count >> queries_count;

    tree.resize(4 * cities_count);
    build_tree(1, 0, cities_count - 1, seats_count);
    
    int start, end, seats;
    for (int i = 0; i < queries_count; i++)
    {
        cin >> start >> end >> seats;
        start--; end--;

        if (is_available(1, 0, cities_count - 1, start, end - 1, seats))
        {
            cout << "T\n";
            update_tree(1, 0, cities_count - 1, start, end - 1, seats);
        }
        else cout << "N\n";
    }
}   