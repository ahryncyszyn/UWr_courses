#include "drzewo_het.h"

Node* create_node(int column, int row, int attacking_colum, int is_solution)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Alokowanie pamieci sie nie powiodlo\n");
        return NULL;
    }
    new_node -> column = column;
    new_node -> row = row;
    new_node -> attacking_col = attacking_colum;
    new_node -> children = NULL;
    new_node -> num_children = 0;
    new_node -> is_solution = is_solution;
    return new_node;
}

void add_child(Node* parent, Node* child)
{
    if (!parent || !child) return;
    Node** new_children = (Node**)realloc(parent -> children, (parent->num_children + 1) * sizeof(Node*));
    if (new_children == NULL)
    {
        printf("Alokowanie pamieci sie nie powiodlo\n");
        return;
    }
    parent -> children = new_children;
    parent -> children[parent -> num_children] = child;
    parent -> num_children++;
}

void free_node(Node* node)
{
    if (!node) return;
    for (int i = 0; i < node -> num_children; i++)
    {
        free_node(node -> children[i]);
    }
    free(node -> children);
    free(node);
}


void print_tree(Node* root, int depth)
{
    if (!root) return;

    // omijanie pierwszej, pomocniczej node
    if (root -> column != -1) 
    {
        // indentacja
        for (int i = 0; i < depth; i++) printf("| ");

        // prefix zalezny od bycia atakowanym lub nie
        if (root -> attacking_col >= 0) printf("%s ", "+--");
        else printf("%s ", "+-\\");
        
        // teskt opisujacy krok algorytmu
        printf("Kolumna %d wiersz %d", root -> column, root -> row);

        if (root -> attacking_col >= 0) printf(" jest atakowany przez hetmana z kolumny %d", root -> attacking_col);
        else printf(" nie jest atakowany, stawiamy hetmana");

        if (root -> is_solution) printf(" - SUKCES!\n");
        else printf("\n");
    }

    // drukowanie wszystkich dzieci z glebokoscia o jeden wieksza
    for (int i = 0; i < root -> num_children; i++)
    {
        print_tree(root -> children[i], depth + 1);
    }
}