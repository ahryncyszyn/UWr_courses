
#include "trees.h"
#include <limits.h>
#include <stdio.h>

int is_BST(node* root, int min, int max)
{
    if (root == NULL) return 1;
    if (root -> val < min || root -> val > max) return 0;
    return is_BST(root -> left, min, root -> val - 1) && is_BST(root -> right, root -> val + 1, max);
}
    
int main()
{
    node* root = utworz(4);
    root -> left = utworz(2);
    root -> right = utworz(6);
    root -> left -> left = utworz(1);
    root -> left -> right = utworz(3);
    root -> right -> left = utworz(5);
    root -> right -> right = utworz(7);

    printf("%d\n", is_BST(root, INT_MIN, INT_MAX));
    delete_tree(root);
    return 0;
}