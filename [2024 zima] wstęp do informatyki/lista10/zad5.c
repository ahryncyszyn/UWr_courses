#include <stdio.h>
#include <stdlib.h>

struct list {
    struct elem* head;
    struct elem* tail;
};

struct elem {
    int val;
    struct elem* next;
};

struct elem* utworzElem(int nval)
{
    struct elem *nowa = (struct elem*)malloc(sizeof(struct elem));
    nowa -> val = nval;
    nowa -> next = NULL;
    return nowa;
}

struct list* utworzLis(int val)
{
    struct list* lis = (struct list*)malloc(sizeof(struct list));
    if (lis != NULL)
    {
        struct elem* nowy_element = utworzElem(val);
        lis -> head = nowy_element;
        lis -> tail = nowy_element;
    }
    return lis;
}

void wypisz(struct list* lis)
{
    struct elem* curr = lis -> head;
    while (curr != NULL)
    {
        printf("%d\n", curr -> val);
        curr = curr -> next;
    }
}

struct list* nowaKoniec(struct list* lis, int nval)
{
    struct elem* nowy_elem = utworzElem(nval);
    if (lis -> tail == NULL)
    {
        lis -> head = nowy_elem;
    }
    else
    {
        lis -> tail -> next = nowy_elem;
    }
    lis -> tail = nowy_elem;
    return lis;
}

struct list* dodajListe(struct list* lis1, struct list* lis2)
{
    lis1 -> tail -> next = lis2 -> head;
    lis1 -> tail = lis2 -> tail;
    lis2 -> head = lis1 -> head;
    return lis1;
}

struct list* usunzPoczatku(struct list* lis)
{
    struct elem* do_usuniecia = lis -> head;
    free(do_usuniecia);
    lis -> head = lis -> head -> next;
    return lis;
}

struct list* dodajDoPoczatku(struct list* lis, int nval)
{
    struct elem* nowy_elem = utworzElem(nval);
    nowy_elem -> next = lis -> head;
    lis -> head = nowy_elem;
    return lis;
}

int main()
{
    int nval = 5;
    
}