// Aleksandra Hryncyszyn, 353636

#include "fold.h"

// tworzenie elementu listy
list cons(PWT content, list tail) 
{
    list curr = tail;
    while (curr != NULL)
    {   
        if (curr -> content.type != content.type) return NULL;
        curr = curr -> next;
    }
    
    list new_elem = malloc(sizeof(struct listelem));
    if (!new_elem) return NULL;
    new_elem -> content = content;
    new_elem -> next = tail;
    return new_elem;
}

// drukowanie listy
void lprint(list l) 
{
    while (l) 
    {
        if (l -> content.type == 'i') printf("%ld ", *(long *)l->content.ptr);
        else if (l -> content.type == 's') printf("%s ", (char *)l->content.ptr);
        l = l -> next;
    }
    printf("\n");
}

// przyjmuje liste i wskaznik na funkcje ktora przyjmuje i zwraca PWT
// przetwrza rekurencyjnie kazdy element listy przez funkcje f
list map(list l, PWT (*f) (PWT) ) 
{
    if (l == NULL) return NULL;
    return cons(f(l -> content), map(l -> next, f));
}

// tworzy liste liczb zamienionych na dodatnie
list take_abs(list numlist)
{
    return map(numlist, abs_aux);
}

// obsluguje tylko PWT typu 'i'
// tworzy nowa zmienna z warotscia bezwzgledna 
// liczby przechowywanej w p
PWT abs_aux(PWT p) 
{
    if (p.type != 'i') return (PWT){NULL, 'n'};
    long *val = malloc(sizeof(long));
    if (!val) return (PWT){NULL, 'n'};
    *val = labs(*(long *)p.ptr);
    return (PWT){val, 'i'};
}

// tworzy liste dlugosci napisow z oryginalnej listy
list take_strlen(list strlist)
{
    return map(strlist, strlen_aux);
}

// obsluguje tylko PWT typu 's'
// tworzy nowa zmienna z dlugoscia
// napisu przechowywanego w p
PWT strlen_aux(PWT p) 
{
    if (p.type != 's') return (PWT){NULL, 'n'};

    long *len = malloc(sizeof(long));
    if (!len) return (PWT){NULL, 'n'};
    *len = strlen((char *)p.ptr);
    return (PWT){len, 'i'};
}

#ifdef FOLDL_ITER
// agreguje wartosci listy od lewej (glowy) do prawej
PWT foldl_iterative(list l, PWT initval, PWT (*agg)(PWT, PWT) )
{
    printf("uzywanie iteratywnej wersji foldl\n");
    while (l != NULL) 
    {
        initval = agg(initval, l -> content);
        l = l -> next;
    }
    return initval;
}
#else
// agreguje wartosci listy od lewej (glowy) do prawej
PWT foldl_recursive(list l, PWT initval, PWT (*agg)(PWT, PWT) )
{
    if (l == NULL) return initval;
    return foldl_recursive(l -> next, agg(initval, l -> content), agg);
}
#endif

// agreguje wartosci listy od prawej (ogona) do lewej
PWT foldr(list l, PWT initval, PWT (*agg)(PWT, PWT) )
{
    if (l == NULL) return initval;
    return agg(l -> content, foldr(l -> next, initval, agg));
}

// zwraca dlugosc listy
long len(list l)
{
    PWT initval = {malloc(sizeof(long)), 'i'};
    if (initval.ptr == NULL) return 0;
    *(long *)initval.ptr = 0;

    PWT res = foldl(l, initval, len_aux);
    long result = *(long *)res.ptr;
    free(res.ptr);
    return result;
}

// ze wzgledu na typ foldl, fukcja agregujaca musi przyjmowac dwa arguemnty PWT
// curr_len przechowuje licznik dlugosci
PWT len_aux(PWT curr_len, PWT _) 
{
    (void) _; // 'uzycie' zeby kompilator nie narzekal
    *(long *)curr_len.ptr += 1;
    return curr_len;
}

// sumuje wszystkie wartosci liczbowe w liscie
long sum(list numlist)
{
    PWT initval = {malloc(sizeof(long)), 'i'};
    if (initval.ptr == NULL) return 0;
    *(long *)initval.ptr = 0;

    PWT res = foldl(numlist, initval, sum_aux);
    long result = *(long *)res.ptr;
    free(res.ptr);
    return result;
}

// weryfikuje czy typ to 'i'
// dodaje wartosc do sumy
PWT sum_aux(PWT curr_sum, PWT elem) 
{
    if (elem.type != 'i') return curr_sum;
    *(long *)curr_sum.ptr += *(long *)elem.ptr;
    return curr_sum;
}

// sumuje dlugosci napisow w liscie
long totlen(list strlist) 
{
    PWT initval = {malloc(sizeof(long)), 'i'};
    if (initval.ptr == NULL) return 0;
    *(long *)initval.ptr = 0;

    PWT res = foldl(strlist, initval, totlen_aux);
    long result = *(long *)res.ptr;
    free(res.ptr);
    return result;
}

// weryfikuje czy typ to 's'
// dodaje dlugosc slowa do sumy dlugosci
PWT totlen_aux(PWT curr_len, PWT elem) 
{
    if (elem.type != 's') return curr_len;
    *(long *)curr_len.ptr += strlen((char *)elem.ptr);
    return curr_len;
}

// konkatenuje wszystkie napisy w liscie
char *cat(list strlist) 
{
    PWT init = {calloc(1, 1), 's'};
    PWT res = foldl(strlist, init, cat_aux);
    return (char *)res.ptr;
}

// weryfikuje czy typ to 's'
// zwieksza pamiec na napis 
PWT cat_aux(PWT acc, PWT elem) 
{
    if (elem.type != 's') return acc;
    size_t new_size = strlen((char *)acc.ptr) + strlen((char *)elem.ptr) + 1;
    char *new_str = realloc(acc.ptr, new_size);
    if (!new_str) return acc;
    strcat(new_str, (char *)elem.ptr);
    return (PWT){new_str, 's'};
}

// odwraca liste
list rev(list l) 
{
    // jako poczatkowa wartosc przekazuje NULL
    return foldl(l, (PWT){NULL, 'n'}, rev_aux).ptr;
}

PWT rev_aux(PWT curr_list, PWT elem) 
{
    return (PWT){cons(elem, (list)curr_list.ptr), 'n'};
}