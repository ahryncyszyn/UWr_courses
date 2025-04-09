#include "graph.h"

void DFS(graph* graph, int u, int* visited, int* count)
{
    visited[u] = 1;
    node* curr = graph -> adjList[u];
    while (curr != NULL)
    {
        int v = curr -> vertex;
        if (!visited[v]) 
        {
            (*count)++;
            DFS(graph, v, visited, count);
        }
        curr = curr -> next;
    }
}

int is_bridge(graph* graph, int u, int v)
{
    int vertices_num = graph -> vertices;
    int visited[vertices_num];
    for (int i = 0; i < vertices_num; i++) visited[i] = 0;

    int count_before = 0;
    DFS(graph, u, visited, &count_before);

    // usuniecie krawdzi (u, v) z grafu
    remove_edge(graph, u, v);
    remove_edge(graph, v, u);

    for (int i = 0; i < vertices_num; i++) visited[i] = 0;
    int count_after = 0;
    DFS(graph, u, visited, &count_after);
    printf("Liczba osiagnietych wierzcholkow przed usunieciem: %d, po: %d\n", count_before, count_after);

    add_edge(graph, u, v);
    add_edge(graph, v, u);
    return (count_after != count_before);
}

void count_all_bridges(graph* graph)
{
    int count = 0;
    node* curr;
    for (int u = 0; u < graph -> vertices; u++)
    {
        curr = graph -> adjList[u];
        while (curr != NULL)
        {
            if (is_bridge(graph, u, curr -> vertex)) count++;
            curr = curr -> next;
        }
    }
    printf("%d mostow\n", count);
}

int main()
{
    graph* g = create_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 3, 4);

    if (is_bridge(g, 1, 3)) printf("krawedz (3, 4) jest mostem\n");
    //if (is_bridge(g, 0, 1)) printf("krawedz (0, 2) jest mostem\n");
    count_all_bridges(g);

    free_graph(g);
    return 0;
}
