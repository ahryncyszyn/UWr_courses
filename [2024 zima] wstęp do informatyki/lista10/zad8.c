
#include "linked_list.h"

void rozdzielListe(struct elem* lista, struct elem** dodatnie, struct elem** ujemne)
{
    if (lista == NULL) return;
    
    *dodatnie = NULL; 
    *ujemne = NULL;
    struct elem* curr = lista;

    while (curr -> next != NULL)
    {
        struct elem* next_elem = curr -> next;
        if (curr -> val > 0)
        {
            curr -> next = *dodatnie;
            *dodatnie = curr; 
        }
        else if (curr -> val < 0)
        {
            curr -> next = *ujemne;
            *ujemne = curr;
        }
        curr = next_elem;
    }
}

// Funkcja do wypisania listy
void wypiszListe(struct elem* lista) {
    struct elem* curr = lista;
    while (curr != NULL) {
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main() {
    // Tworzymy przykładową listę
    struct elem* lista = utworz(-5);
    lista->next = utworz(3);
    lista->next->next = utworz(-2);
    lista->next->next->next = utworz(8);
    lista->next->next->next->next = utworz(-1);

    printf("Original list:\n");
    wypiszListe(lista);

    // Rozdzielamy listę na dwie
    struct elem* lista_dodatnia = NULL;
    struct elem* lista_ujemna = NULL;
    rozdzielListe(lista, &lista_dodatnia, &lista_ujemna);

    printf("Lista dodatnia:\n");
    wypiszListe(lista_dodatnia);

    printf("Lista ujemna:\n");
    wypiszListe(lista_ujemna);

    return 0;
}