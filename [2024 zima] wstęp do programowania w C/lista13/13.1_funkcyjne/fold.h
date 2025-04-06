// Aleksandra Hryncyszyn, 353636

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef FOLDL_ITER
    #define foldl foldl_iterative
#else
    #define foldl foldl_recursive
#endif

struct pointer_with_type {
    void *ptr;
    char type; // 'i' dla liczb i 's' dla napisow
};
typedef struct pointer_with_type PWT;

struct listelem {
    PWT content;
    struct listelem *next;
};
typedef struct listelem * list;

list cons(PWT content, list tail);
void lprint(list l);

list map(list l, PWT (*f) (PWT) );

list take_abs(list numlist);
PWT abs_aux(PWT p);
list take_strlen(list strlist);
PWT strlen_aux(PWT p);

PWT foldl(list l, PWT initval, PWT (*agg)(PWT, PWT) );
PWT foldr(list l, PWT initval, PWT (*agg)(PWT, PWT) );

long len(list l);
PWT len_aux(PWT acc, PWT _);

long sum(list numlist);
PWT sum_aux(PWT acc, PWT elem);

long totlen(list strlist);
PWT totlen_aux(PWT acc, PWT elem);

char *cat(list strlist);
PWT cat_aux(PWT acc, PWT elem);

list rev(list l);
PWT rev_aux(PWT acc, PWT elem);

