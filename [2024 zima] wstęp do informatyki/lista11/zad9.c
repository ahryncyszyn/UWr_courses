
#include "trees.h"
/*
             10                              11
           /     \         delete(10)      /    \
          7       15       --------->    7        15 
         /  \    /  \                   /  \        \ 
        5    8  11   18                5    8        18

             10                              10
           /     \         delete(15)      /    \
          7       15       --------->    7       11 
         /  \    /                      /  \      
        5    8  11                     5    8

*/

node* delete_node(node* root, int dval)
{
    node* curr = root;
    node* prev = NULL;

    // prev to bedzie rodzic curr, ktora ma wartosc val
    while (curr != NULL && curr -> val != dval) 
    {
        prev = curr;
        if (dval < curr -> val) curr = curr -> left;
        else curr = curr -> right;
    }

    // nie ma takiego elementu
    if (curr == NULL) 
        return root;

    // sprawdzic czy ma maks 1 dziecko
    if (curr -> left == NULL || curr -> right == NULL) 
    {
        node* newCurr;

        // lewe dziecko nie istnieje
        if (curr -> left == NULL) newCurr = curr -> right;
        else newCurr = curr -> left;

        // czy trzeba usunac root
        if (prev == NULL) return newCurr;

        // sprawdzic czy curr bylo prawym czy lewym dzieckiem prev
        // i zalczyc newcurr na jego miejsce
        if (curr == prev -> left) prev -> left = newCurr;
        else prev -> right = newCurr;

        free(curr);
    } else 
    {
        // ma dwoje dzieci
        node* p = NULL;
        node* temp = curr -> right;
        
        // szukanie najmniejszego elementu w prawym poddrzewie
        while (temp -> left != NULL) 
        {
            p = temp;
            temp = temp -> left;
        }

        // zamiana wartosci
        if (p != NULL) p -> left = temp -> right;
        else curr -> right = temp -> right;

        curr -> val = temp -> val;
        free(temp);
    }

    return root;
}

int main()
{
    node* root = utworz(5);
    root -> left = utworz(3);
    root -> right = utworz(7);
    root -> left -> left = utworz(2);
    root -> left -> right = utworz(4);
    root -> right -> left = utworz(6);
    root -> right -> right = utworz(8);

    root = delete_node(root, 4);
    print_in_order(root);
    delete_tree(root);
    return 0;
}