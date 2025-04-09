
#include "trees.h"

/*
            u                           v
        v       c       ->        b             u   
    b    a                                  a       c

*/

node* rotate_tree(node* root)
{
    if (root == NULL || root -> left == NULL) return NULL;

    node* new_root = root -> left;
    root -> left = new_root -> right;
    new_root -> right = root;
    return new_root;
}

int main()
{
    node* root = utworz(5);
    root -> left = utworz(4);
    root -> left -> left = utworz(3);
    root -> right = utworz(6);
    root -> right -> right = utworz(7);
    print_in_order(root);
    printf("----------------\n");
    node* new_root = rotate_tree(root);
    print_in_order(new_root);
    delete_tree(root);
    delete_tree(new_root);
}