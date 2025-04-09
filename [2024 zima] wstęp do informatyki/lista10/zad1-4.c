
#include "linked_list.h"

struct elem* nowaKoniec1(struct elem* lis, int nval)
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

struct elem* usunOstatni(struct elem* lis)
{  
    if (lis == NULL) return NULL;
    if (lis -> next == NULL)
    {
        free(lis);
        return NULL;
    }

    struct elem* curr = lis;
    struct elem* prev = NULL;
    while (curr -> next != NULL)
    {
        prev = curr;
        curr = curr -> next;
    }

    prev -> next = NULL;
    free(curr);
    return lis;
}

struct elem* dodajListe(struct elem* lis1, struct elem* lis2)
{
    if (lis1 == NULL) return lis2;

    struct elem* curr = lis1;
    while (curr -> next != NULL)
    {
        curr = curr -> next;
    }
    curr -> next = lis2;
    return lis1;
}

struct elem* usunVal(struct elem* lis, int uval)
{
    if (lis == NULL) return NULL;

    struct elem* curr = lis;
    struct elem* prev = NULL;
    struct elem* to_delete;

    while (curr != NULL)
    {
        if (curr -> val == uval)
        {
            to_delete = curr; // zapisujemy element do usuniecia
            if (prev == NULL) // poczatek listy
            {
                lis = curr -> next;
            }
            else // srodek listy
            {
                prev -> next = curr -> next;
            }
            curr = curr -> next;
            free(to_delete);
        }
        else
        {
            prev = curr;
            curr = curr -> next;
        }
    }
    return lis;
}

int main()
{
    int nval = 5;
    struct elem* lis = utworz(nval);
    nowaKoniec(lis, 8);
    nowaKoniec(lis, 8);
    nowaKoniec(lis, 8);
    wypisz(lis);

    usunVal(lis, 8);
    printf("\nPo usunieciu:\n");
    wypisz(lis);
}

