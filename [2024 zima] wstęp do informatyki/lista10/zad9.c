#include <stdio.h>
#include <stdlib.h>

struct elem
{
    int val;
    struct elem* next;
    struct elem* prev;
};

struct elem* dodajKoniec(struct elem* lista, int nval)
{
    struct elem* nowy = (struct elem*)malloc(sizeof(struct elem));
    nowy -> val = nval;
    nowy -> next = NULL;
    nowy -> prev = NULL;
    
    if (lista == NULL) return nowy;

    struct elem* curr = lista;
    while (curr -> next != NULL)
    {
        curr = curr -> next;
    }
    curr -> next = nowy;
    nowy -> prev = curr;
    return lista;
}

struct elem* usunPocza(struct elem* lista)
{
    if (lista == NULL) return NULL;

    struct elem* do_usuniecia = lista;
    lista = lista -> next;

    if (lista != NULL) lista -> prev = NULL;

    free(do_usuniecia);
    return lista;
}

struct elem* usunKoniec(struct elem* lista)
{
    if (lista == NULL) return NULL;
    if (lista -> next == NULL)
    {
        free(lista);
        return NULL;
    }

    struct elem* curr = lista;
    while (curr -> next != NULL)
    {
        curr = curr -> next;
    }
    curr -> prev -> next = NULL;
    free(curr);
    return lista;
}

void wypiszListe(struct elem* lista)
{
    struct elem* curr = lista;
    while (curr != NULL)
    {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

int main()
{
    struct elem* lista = NULL;

    // Dodanie elementów na koniec
    lista = dodajKoniec(lista, 10);
    lista = dodajKoniec(lista, 20);
    lista = dodajKoniec(lista, 30);
    printf("Lista po dodaniu elementów: ");
    wypiszListe(lista);

    // Usunięcie z początku
    lista = usunPocza(lista);
    printf("Lista po usunięciu z początku: ");
    wypiszListe(lista);

    // Usunięcie z końca
    lista = usunKoniec(lista);
    printf("Lista po usunięciu z końca: ");
    wypiszListe(lista);

    return 0;
}