#include "fold.h"

int main(void) {
    long nums[] = {3, 14, -15, -128, 0, 7};
    list nlist = NULL;
    for (int i = sizeof nums / sizeof(long); i-- > 0; )
        nlist = cons((PWT) {(void *) (nums + i), 'i'}, nlist);
    
    lprint(rev(take_abs(nlist)));
    printf(u8"Długość: %ld\n", len(nlist));
    printf("Suma: %ld\n", sum(nlist));
    
    char* strings[] = {"Ala", "Ma", "Kota"};
    list slist = NULL;
    for (int i = sizeof strings / sizeof(char *); i-- > 0; )
        slist = cons((PWT) {(void *) strings[i], 's'}, slist);
    
    lprint(slist);
    lprint(take_strlen(slist));
    printf(u8"Łączna długość napisów: %ld\n", totlen(slist));
    printf(u8"Połączone napisy: %s\n", cat(slist));
    
    return 0;
}
