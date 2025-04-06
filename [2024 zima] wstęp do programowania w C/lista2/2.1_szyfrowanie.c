#include <stdio.h>

char na_zaszyfrowane(char do_zamiany)
{
    char samogloski[5] = {'a', 'e', 'i', 'o', 'u'};
    int k = 2; // przesuniecie

    for(int i = 0; i < 5; i++)
    {
        if (do_zamiany == samogloski[i]) // male litery
        {
            return samogloski[(i + k) % 5];
        }
        else if ((do_zamiany - 'A' + 'a') == samogloski[i]) // wielkie litery
        {
            return (samogloski[(i + k) % 5] - 'a' + 'A');
        }
    }
    return do_zamiany; // spolgloski i inne
}

int main(void)
{
    int c;
    while((c = getchar()) != EOF)
    {
        putchar(na_zaszyfrowane(c));
    }

    return 0;
}

