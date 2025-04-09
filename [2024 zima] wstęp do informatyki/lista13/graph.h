#include <stdio.h>
#include <stdlib.h>

// wezel listy sąsiedztwa
typedef struct Node {
    int vertex;
    struct Node* next;
} node;

node* create_node(int vertex, node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node -> vertex = vertex;
    new_node -> next = next;
    return new_node;
}

// lista sąsiedztwa grafu
typedef struct Graph {
    int vertices;
    node** adjList;
} graph;

graph* create_graph(int vertices)
{
    graph* g = (graph*)malloc(sizeof(graph));
    g -> vertices = vertices;
    g -> adjList = (node**)malloc(vertices * sizeof(node*));
    for (int i = 0; i < vertices; i++)
        g -> adjList[i] = NULL;
    return g;
}

void remove_edge(graph* graph, int u, int v)
{
    node* prev = NULL;
    node* curr = graph -> adjList[u];
    while (curr != NULL && curr -> vertex != v)
    {
        prev = curr;
        curr = curr -> next;
    }
    if (curr != NULL)
    {
        if (prev == NULL) graph -> adjList[u] = curr -> next;
        else prev -> next = curr -> next;
        free(curr);
    }
}

void add_edge(graph* graph, int src, int dest)
{
    node* new_node = create_node(dest, graph -> adjList[src]);
    graph -> adjList[src] = new_node;
}

void free_graph(graph* graph)
{
    for (int i = 0; i < graph -> vertices; i++)
    {
        node* curr = graph -> adjList[i];
        while (curr != NULL)
        {
            node* temp = curr;
            curr = curr -> next;
            free(temp);
        }
    }
    free(graph -> adjList);
    free(graph);
}

