#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

// skladowa silnie spojna - spojny podgraf, w ktorym z kazdego wierzcholka da sie dojsc do kazdego innego
// numerowanie postorder - puszczenie DFS i przypisywanie numeru przy wychodzeniu z wierzcholka
// reprezentant spojnej - max({post(a) | a nalezacy do spojnej A}) - wierzcholek z najwiekszym numerem, czyli ten z ktorego wyszlismy najpozniej
// lemat - jezeli istnieje krawedz miedzy skladowa A a skladowa B to repr(A) > repr(B)
// graf skondensowany jest acykliczny, bo gdyby istnial cykl to caly graf bylby w jednej skladowej silnie spojnej
// odwrocenie krawedzi uniemozliwia przejscie z jednej skladowej do drugiej jezeli trzymamy sie kolejnosci z pierwszeog DFS
// bo startujemy z wierzcholka ktory nie ma zadnych krawedzi wchodzacych (czyli w odwroconym grafie nie ma wychodzacych)

vector<vector<int>> graph;
vector<vector<int>> graph_rev;
vector<vector<int>> sccs;
vector<int> sccs;
vector<bool> visited;
stack<int> st;

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

void dfs2(int node, vector<int>& component)
{
    if (visited[node]) return;
    visited[node] = true;
    component.push_back(node);
    for (int neighb : graph_rev[node])
    {
        dfs2(neighb, component);
    }
}

int find_SCCs(int N)
{
    for (int i = 1; i <= N; i++) dfs1(i);

    visited.assign(N + 1, false);
    while (!st.empty())
    {
        int curr = st.top();
        st.pop();
        if (!visited[curr])
        {
            vector<int> component;
            dfs2(curr, component);
            sccs.push_back(component);
        }
    }
    return sccs.size();
}

int main()
{
    int N, M, u, v;
    cin >> N >> M;

    graph.resize(N + 1);
    graph_rev.resize(N + 1);
    visited.resize(N + 1);
    sccs.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }

    int scc_count = find_SCCs(N);
    for (auto& comp : sccs) sort(comp.begin(), comp.end());
    sort(sccs.begin(), sccs.end(), 
        [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    for (int i = 0; i < scc_count; i++)
    {
        for (int node : sccs[i]) sccs[node] = i + 1;
    }

    cout << scc_count << "\n";
    for (int i = 1; i <= N; i++) cout << sccs[i] << " ";
}   