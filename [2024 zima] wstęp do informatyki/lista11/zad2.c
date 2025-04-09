
#include "trees.h"

int elements_in_tree(node* root)
{
    if (root == NULL) return 0;
    return 1 + elements_in_tree(root -> left) + elements_in_tree(root -> right);
}

int main()
{
    node* root = utworz(1);
    root -> left = utworz(2);
    root -> right = utworz(3);
    root -> left -> left = utworz(4);
    root -> left -> right = utworz(5);
    root -> right -> left = utworz(6);
    root -> right -> right = utworz(7);

    printf("%d\n", elements_in_tree(root));
    delete_tree(root);
    return 0;
}