
#include "trees.h"


// O(n) - we visit every node once
void print_all_positive(node* root)
{
    if (root == NULL) return;
    if (root -> left != NULL && root -> left -> val > 0)
    {
        print_all_positive(root -> left);
    }
    if (root -> val > 0) printf("%d\n", root -> val);
    print_all_positive(root -> right);
}

int main()
{
    node* root = utworz(1);
    root -> left = utworz(-2);
    root -> right = utworz(4);
    root -> left -> left = utworz(-3);
    root -> left -> right = utworz(-1);
    root -> right -> left = utworz(3);
    root -> right -> right = utworz(5);
    print_all_positive(root);
    delete_tree(root);
}