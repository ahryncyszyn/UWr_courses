
#include "linked_list.h"

elem* usunOstatPar(elem* lista)
{
    if (lista == NULL) return NULL;

    int last_even = -1;
    elem* curr = lista;

    while (curr != NULL)
    {
        if (curr -> val % 2 == 0) last_even = curr -> val;
        curr = curr -> next;
    }

    if (last_even == -1) return lista;

    curr = lista;
    elem* prev = NULL;

    while (curr -> val != last_even)
    {   
        prev = curr;
        curr = curr -> next;
    }

    prev -> next  = curr -> next;
    free(curr);
}

int main()
{
    elem* lista = utworz(1);
    lista = nowaKoniec(lista, 2);
    lista = nowaKoniec(lista, 3);
    lista = nowaKoniec(lista, 4);
    lista = nowaKoniec(lista, 5);

    wypisz(lista);
    printf("----------------\n");
    usunOstatPar(lista);
    wypisz(lista);

    return 1;
}