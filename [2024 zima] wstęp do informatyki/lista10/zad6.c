
#include "linked_list.h"

void wypiszOdwrotnie(struct elem* lis)
{
    if (lis == NULL) return;
    wypiszOdwrotnie(lis -> next);
    printf("%d\n", lis -> val);
}

int main()
{
    struct elem* lista = utworz(1);
    nowaKoniec(lista, 2);
    nowaKoniec(lista, 3);
    nowaKoniec(lista, 4);
    nowaKoniec(lista, 5);
    wypiszOdwrotnie(lista);
}
