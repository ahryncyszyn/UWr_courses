#include "linked_list.h"

struct elem* scalListy(struct elem* lista1, struct elem* lista2)
{
    struct elem dummy;
    struct elem* curr = &dummy;
    dummy.next = NULL;

    while(lista1 != NULL && lista2 != NULL)
    {
        if (lista1 -> val <= lista2 -> val) 
        {
            curr -> next = lista1;
            lista1 = lista1 -> next;
        } 
        else 
        {
            curr -> next = lista2;
            lista2 = lista2 -> next;
        }
        curr = curr -> next;
    }

    if (lista1 != NULL) 
    {
        curr -> next = lista1;
    } 
    else 
    {
        curr -> next = lista2;
    }
    return dummy.next;
}

int main()
{
    struct elem* lista1 = utworz(1);
    lista1->next = utworz(3);
    lista1->next->next = utworz(5);

    struct elem* lista2 = utworz(2);
    lista2->next = utworz(4);
    lista2->next->next = utworz(6);

    printf("Lista 1: ");
    wypisz(lista1);
    printf("Lista 2: ");
    wypisz(lista2);

    struct elem* wynik = scalListy(lista1, lista2);

    printf("Scalona lista: ");
    wypisz(wynik);

    return 0;
}