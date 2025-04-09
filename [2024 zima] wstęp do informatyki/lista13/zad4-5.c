
#include "graph.h"

void find_path(graph* graph, int start, int destination)
{
    int vertices_num = graph -> vertices;
    int visited[vertices_num];
    int parent[vertices_num];
    for (int i = 0; i < vertices_num; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    // powinna byc lista wiazana ale mi sie nie chce
    int queue[5*vertices_num]; 
    int front = 0, end = 0;

    visited[start] = 1;
    queue[end] = start; 
    end++;

    int path_found = 0;
    while (front < end)
    {
        int vert = queue[front];
        front++;

        if (vert == destination)
        {
            path_found = 1;
            break;
        }

        node* curr = graph -> adjList[vert];
        while (curr != NULL)
        {
            int neighbour = curr -> vertex;
            if (!visited[neighbour])
            {
                visited[neighbour] = 1;
                parent[neighbour] = vert;
                queue[end] = neighbour;
                end++;
            }
            curr = curr -> next;
        }
    }

    if (path_found)
    {
        printf("Ścieżka z %d do %d: ", start, destination);
        int path[vertices_num];
        int length = 0;

        // odtwarzanie ścieżki
        for (int at = destination; at != -1; at = parent[at]) 
        {
            path[length++] = at;
        }

        // odwrócenie ścieżki, zeby była od startu
        for (int i = length - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else printf("Brak ścieżki z %d do %d.\n", start, destination);
}


int find_shortest_path_len(graph* graph, int start, int destination)
{
    int vertices_num = graph -> vertices;
    int visited[vertices_num];
    int distance[vertices_num];
    int parent[vertices_num];
    for (int i = 0; i < vertices_num; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = -1;
    }

    // powinna byc lista wiazana ale mi sie nie chce
    int queue[5*vertices_num]; 
    int front = 0, end = 0;

    visited[start] = 1;
    distance[start] = 0;
    queue[end] = start; 
    end++;

    while (front < end)
    {
        int vert = queue[front];
        front++;

        if (vert == destination) break;

        node* curr = graph -> adjList[vert];
        while (curr != NULL)
        {
            int neighbour = curr -> vertex;
            if (!visited[neighbour])
            {
                visited[neighbour] = 1;
                parent[neighbour] = vert;
                distance[neighbour] = distance[vert] + 1;

                queue[end] = neighbour;
                end++;
            }
            curr = curr -> next;
        }
    }

    if (distance[destination] >= 0)
    {
        printf("Ścieżka z %d do %d: ", start, destination);
        int path[vertices_num];
        int length = 0;

        for (int at = destination; at != -1; at = parent[at]) 
        {
            path[length++] = at;
        }

        for (int i = length - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return distance[destination];
    }
    return -1;
}

int main() 
{
    graph* g = create_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 3, 4);

    find_path(g, 0, 4);
    printf("%d", find_shortest_path_len(g, 0, 4));

    free_graph(g);
    return 0;
}