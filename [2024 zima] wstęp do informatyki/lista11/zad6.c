
#include "trees.h"

int elements_in_tree(node* root)
{
    if (root == NULL) return 0;
    return 1 + elements_in_tree(root -> left) + elements_in_tree(root -> right);
}

// val w root1 < val w root2
node* combine_trees(node* root1, node* root2)
{
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;

    node* max_node = root1;
    while (max_node -> right != NULL)
    {
        max_node = max_node -> right;
    }
    max_node -> right = root2;
    return root1;
}

int main()
{
    node* root1 = utworz(1);
    root1 -> left = utworz(2);
    root1 -> right = utworz(3);
    root1 -> left -> left = utworz(4);
    root1 -> left -> right = utworz(5);
    root1 -> right -> left = utworz(6);
    root1 -> right -> right = utworz(7);

    node* root2 = utworz(8);
    root2 -> left = utworz(9);
    root2 -> right = utworz(10);
    root2 -> left -> left = utworz(11);
    root2 -> left -> right = utworz(12);
    root2 -> right -> left = utworz(13);
    root2 -> right -> right = utworz(14);

    node* combined = combine_trees(root1, root2);
    printf("%d\n", elements_in_tree(combined));
    delete_tree(combined);
    return 0;
}