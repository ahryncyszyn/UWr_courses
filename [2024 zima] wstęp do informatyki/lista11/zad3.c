
#include "trees.h"

int tree_height(node* root)
{
    if (root == NULL) return 0;
    int left_height = tree_height(root -> left);
    int right_height = tree_height(root -> right);
    return 1 + (left_height > right_height ? left_height : right_height);
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

    printf("%d\n", tree_height(root));
    delete_tree(root);
    return 0;
}