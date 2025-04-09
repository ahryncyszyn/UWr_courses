
#include "trees.h"

node* insert(node* root, int x)
{
    node* new_node = utworz(x);
    if (root == NULL) return new_node;

    // szukanie rodzica
    node* parent = NULL;
    node* curr = root;
    while (curr != NULL) 
    {
        parent = curr;
        if (curr -> val > x) curr = curr -> left;
        else if (curr -> val < x) curr = curr -> right;
        else return root;
    }

    // wyznaczenie po ktorej stronie jest dzieckiem
    if (parent -> val > x) parent -> left = new_node;
    else parent -> right = new_node;
    return root;
}

int main()
{
    node* root = utworz(7);
    root -> left = utworz(3);
    root -> right = utworz(8);
    root -> left -> left = utworz(2);
    root -> left -> right = utworz(4);
    insert(root, 5);
    print_in_order(root);
}