#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// wejscie: n - liczba 50-cyfrowych liczb (n <= 100)
//          n * 50-cyfrowa liczba
// wyjście: 9 pierwszych cyfr z sumy n cyfr na wyjsciu

#define MAX_DIGITS 60 // uwzglednia +10 miejsc dla przeniesien
#define MAX_NUMBERS 100
#define DIGITS 9
void add_number(char num[], char bigsum[], char temp[]);
void print_first_digits(char bigsum[], int digits);

int main()
{
    int n;
    scanf("%d", &n);
    // tablica na wynikowa sume
    char bigsum[MAX_DIGITS + 1] = {};
    bigsum[MAX_DIGITS] = '\0';

    // tablica na pojedyncza wczytana liczbe
    char num[MAX_DIGITS] = {};
    
    // tablica pomocniczna przy dodawaniu
    char temp[MAX_DIGITS + 1] = {};

    // dodawanie liczb do sumy
    for (int i = 0; i < n; i++)
    {
        scanf("%s", num);

        // zapisywanie wyniku dodawania liczby do bigsum w temp
        add_number(num, bigsum, temp);

        // przekopiowanie wyniku do bigsum
        strcpy(bigsum, temp);
    }

    // wypisywanie wyniku (pierwszych 9 cyfr)
    int digits = DIGITS;
    print_first_digits(bigsum, digits);
}

void add_number(char num[], char bigsum[], char temp[])
{
    int len_num = strlen(num);
    int len_sum = strlen(bigsum);
    int carry = 0;
    int cyfra_l, cyfra_s, suma;

    // wyzerowanie tablicy na wynik
    for (int i = 0; i < MAX_DIGITS; i++) temp[i] = '0';

    // dodawanie od konca
    for (int i = 0; i < len_num || i < len_sum || carry; i++)
    {
        cyfra_l = (i < len_num) ? num[len_num - 1 - i] - '0' : 0;
        cyfra_s = (i < len_sum) ? bigsum[len_sum - 1 - i] - '0' : 0;

        suma = cyfra_l + cyfra_s + carry;
        temp[MAX_DIGITS - 1 - i] = (suma % 10) + '0';
        carry = suma / 10;
    }

    temp[MAX_DIGITS] = '\0';
}

void print_first_digits(char bigsum[], int digits)
{
    int position = 0;
    int len_sum = strlen(bigsum);
    while (position < len_sum && bigsum[position] == '0') position++;

    for (int i = position; i < position + digits && position < len_sum; i++)
    {
        printf("%c", bigsum[i]);
    }
}