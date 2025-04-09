

#include "linked_list.h"

struct elem* odwrocListe(struct elem* lis1)
{
    struct elem* prev = NULL;
    struct elem* curr = lis1;
    struct elem* next = NULL;

    while (curr != NULL)
    {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main()
{
    struct elem* lista = utworz(1);
    lista->next = utworz(2);
    lista->next->next = utworz(3);

    printf("Oryginalna lista: ");
    wypisz(lista);

    // Odwracanie listy
    lista = odwrocListe(lista);

    printf("Odwrócona lista: ");
    wypisz(lista);

    return 0;
}