#include <stdio.h>
#include <stdlib.h>

typedef struct elem elem;

struct elem 
{   
    int val;
    struct elem * next;
};

void wypisz(struct elem *lis)
{
    while (lis != NULL) 
    {
        printf("%d\n",lis->val);
        lis = lis->next;
    }
}

struct elem* utworz(int nval)
{
    struct elem *nowa = (struct elem*)malloc(sizeof(struct elem));
    nowa -> val = nval;
    nowa -> next = NULL;
    return nowa;
}

struct elem* nowaKoniec(struct elem* lis, int nval)
{
    struct elem* new_elem = utworz(nval);
    if (new_elem == NULL) return lis;
    if (lis == NULL) return new_elem;

    struct elem* curr = lis;
    while (curr -> next != NULL)
    {
        curr = curr -> next;
    }
    curr -> next = new_elem;

    return lis;
}