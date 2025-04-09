#include "graph.h"
#include <stdlib.h>

graph* matrix_to_adj_list(int** matrix, int vertices)
{
    graph* graph = malloc(sizeof(graph));
    graph -> vertices = vertices;
    graph -> adjList = (node**)malloc(vertices * sizeof(node*));
    for (int i = 0; i < vertices; i++) graph -> adjList[i] = NULL;

    for (int i = 0; i < vertices; i++) 
    {
        for (int j = 0; j < vertices; j++) 
        {
            if (matrix[i][j] == 1) 
            {  // istnieje krawędź i -> j
                node* new_node = create_node(j, graph -> adjList[i]);
                graph -> adjList[i] = new_node;
            }
        }
    }
    return graph;
}

int** adj_list_to_matrix(graph* graph)
{
    // alokowanie pamieci na macierz sasiedztwa
    int** matrix = (int**)calloc(graph -> vertices, sizeof(int*));
    for (int i = 0; i < graph -> vertices; i++)
    {
        matrix[i] = (int*)calloc(graph -> vertices, sizeof(int));
    }

    node* curr_vert;
    for (int i = 0; i < graph -> vertices; i++)
    {
        curr_vert = graph -> adjList[i];
        while (curr_vert != NULL)
        {
            matrix[i][curr_vert -> vertex] = 1;
            curr_vert = curr_vert -> next;
        }
    }
    return matrix;
}

void printGraph(graph* graph) 
{
    for (int i = 0; i < graph -> vertices; i++) 
    {
        printf("Vertex %d: ", i);
        node* current = graph -> adjList[i];
        while (current != NULL) 
        {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}


void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    int n = 4;
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    int example_matrix[4][4] = 
    {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 1, 1},
        {0, 1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = example_matrix[i][j];
        }
    }

    graph* graph = matrix_to_adj_list(matrix, n);
    printGraph(graph);
    int** result_matrix = adj_list_to_matrix(graph);
    printMatrix(result_matrix, n);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(result_matrix[i]);
    }
    free(matrix);
    free(result_matrix);
    free(graph -> adjList);
    free(graph);
    return 0;
}
