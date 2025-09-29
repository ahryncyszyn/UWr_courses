#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

// dla grafu bez cykli wystarczyloby odpalic dfs
// ale mamy cykle wiec nie bedzie dzialac poprawnie
// trzeba wyznaczyc silnie spojne skladowe, a potem
// policzyc sume monet w kazdej i odpalic dfs na grafie skondensowanym

vector<ll> coins, sccs_coins_sum;
vector<vector<int>> graph, graph_rev, graph_cond;
vector<int> sccs, sccs_sorted, in_degree;
vector<bool> visited;
stack<int> st;

// do wstepnego posortowania na zwyklym grafie
void dfs1(int node)
{
    if (visited[node]) return;
    visited[node] = true;
    for (int neighb : graph[node])
    {
        dfs1(neighb);
    }
    st.push(node);
}

// do wyizolowania sccs na odwroconym grafie
void dfs2(int node, int component_idx)
{
    if (visited[node]) return;
    visited[node] = true;
    sccs[node] = component_idx;
    for (int neighb : graph_rev[node])
    {
        dfs2(neighb, component_idx);
    }
}

// uzywa stosu i dfs do wyznaczenia sccs
int find_SCCs(int N)
{
    visited.assign(N + 1, false);
    for (int i = 1; i <= N; i++) dfs1(i);

    visited.assign(N + 1, false);
    int component_idx = 0;
    while (!st.empty())
    {
        int curr = st.top();
        st.pop();
        if (!visited[curr])
        {
            component_idx++;
            dfs2(curr, component_idx);
        }
    }
    return component_idx;
}

// buduje graf zlozony z silnie spojnych skladowych
void build_condensation_graph(int N, int scc_count)
{
    graph_cond.assign(scc_count + 1, {});
    in_degree.assign(scc_count + 1, 0);

    for (int node = 1; node <= N; node++) 
    {
        for (int neigh : graph[node]) 
        {
            if (sccs[node] != sccs[neigh]) 
            {
                graph_cond[sccs[node]].push_back(sccs[neigh]);
                in_degree[sccs[neigh]]++;
            }
        }
    }
}

// sortowanie topologiczne zeby przy liczeniu zapewnic 
// poprawne kumulowanie sumy monet
void topological_sort(int scc_count)
{
    priority_queue<int, vector<int>, greater<int>> nodes_queue;
    for (int i = 1; i <= scc_count; i++)
    {   
        if (in_degree[i] == 0) nodes_queue.push(i); 
    }

    while (!nodes_queue.empty())
    {   
        int node = nodes_queue.top();
        nodes_queue.pop();
        sccs_sorted.push_back(node);

        for (int neighb : graph_cond[node])
        {
            in_degree[neighb]--;
            if (in_degree[neighb] == 0)
            {
                nodes_queue.push(neighb);
            }
        }
    }
}

// uzywa programowania dynamicznego
ll find_max_coins(int scc_count)
{
    topological_sort(scc_count);
    vector<ll> dp = sccs_coins_sum;

    for (int node : sccs_sorted)
    {
        for (int neighb : graph_cond[node])
        {
            dp[neighb] = max(dp[neighb], dp[node] + sccs_coins_sum[neighb]);
        }
    }
    ll max_sum = *max_element(dp.begin(), dp.end());
    return max_sum;
}

int main()
{
    int N, M, u, v;
    cin >> N >> M;

    // wczytanie monet kazdego wierzcholka
    coins.resize(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> coins[i];
    }

    // wczytanie grafu i jego odwrotnosci
    graph.resize(N + 1);
    graph_rev.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }
    
    // szukanie silnie spojnych skladowych
    sccs.resize(N + 1);
    int scc_count = find_SCCs(N);

    // sumowanie monet w składowych
    sccs_coins_sum.resize(scc_count + 1, 0);
    for (int node = 1; node <= N; node++)
    {
        sccs_coins_sum[sccs[node]] += coins[node];
    }

    // budowa skondesowanego grafu i wyszukanie w nim maksymalnej sumy
    build_condensation_graph(N, scc_count);
    cout << find_max_coins(scc_count);
    return 0;
}