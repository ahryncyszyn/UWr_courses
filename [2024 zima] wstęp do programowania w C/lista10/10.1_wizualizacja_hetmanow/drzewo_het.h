#include <stdlib.h>
#include <stdio.h>

// struct drzewa n-arnego
typedef struct Node 
{
    // wspolrzedne pozycji
    int column;
    int row;

    // -1 jezeli pozycja nie jest atakowana
    int attacking_col; 

    // wskazniki na kolejne przeszukiwane pozycje
    struct Node** children;
    int num_children;

    // 1 jezeli jest rozwiazaniem problemu, 0 w.p.p
    int is_solution;
} Node;

// tworzy drzewo
Node* create_node(int column, int row, int attacking_colum, int is_solution);

// dodaje wskaznik na dziecko do tablicy dzieci rodzica
void add_child(Node* parent, Node* child);

// rekursywnie zwalnia pamiec calego drzewa od danej node
void free_node(Node* node);

// drukuje drzewo wedlug wymagan zadania
void print_tree(Node* root, int depth);
