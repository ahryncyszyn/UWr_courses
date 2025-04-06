// Aleksandra Hryncyszyn, 353636

#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[])
{
    // zapewnienie odpowiedniej liczby argumentow
    if (argc != 2)
    {
        printf("Prosze podac jeden ciag znakow jako argument!\n");
        return 1;
    }

    // stworzenie nowej tablicy na wczytany tekst
    int arglen = strlen(argv[1]);
    char text[arglen];

    // kopiowanie tekstu do tablicy
    for (int i = 0; i <= arglen; i++)
    {
        text[i] = tolower(argv[1][i]);
    }

    // wypisywanie meksykanskiej fali
    for (int i = 0; i < arglen; i++)
    {
        if (text[i] == ' ') continue;

        text[i] = toupper(text[i]);
        printf("%s\n", text);
        text[i] = tolower(text[i]);
    }

    return 0;
}
