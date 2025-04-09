#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    int val;
    node* left;
    node* right;
};

node* utworz(int wart)
{ 
    node* pom;
    pom = (node*) malloc(sizeof(node));
    if (pom == NULL) return NULL;
    pom -> left = NULL;
    pom -> right = NULL;
    pom -> val = wart;
    return pom;
}

void delete_tree(node* root)
{
    if (root == NULL) return;
    delete_tree(root -> left);
    delete_tree(root -> right);
    free(root);
}

void print_in_order(node* root)
{
    if (root == NULL) return;
    print_in_order(root -> left);
    printf("%d\n", root -> val);
    print_in_order(root -> right);
}