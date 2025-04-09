#include <iostream>
#include <vector>
using namespace std;

int dfs(int node, vector<vector<int>> &tree, vector<int> &subtree_size)
{
    for (auto child : tree[node - 1])
    {
        subtree_size[node - 1] += dfs(child, tree, subtree_size) + 1;
    }
    return subtree_size[node - 1];
}

// zlozonosc czas: O(n)
int main()
{
    int N;
    cin >> N;

    vector<vector<int>> tree(N);
    vector<int> subtree_size(N, 0);

    int parent;
    for (int child = 2; child <= N; child++)
    {
        std::cin >> parent;
        tree[parent - 1].push_back(child);
    }

    dfs(1, tree, subtree_size);

    for (int i = 0; i < N; i++)
    {
        cout << subtree_size[i] << " ";
    }
    return 0;
}