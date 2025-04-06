#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// slowo a da sie ulozyc ze slowa b przez wyrzucenie jakis lub zadnych liter i przestawienie pozostalych

// wejscie: 0 < n <= 16 - liczba zestawow slow
//          n wierszy złozonych z:
//          k <= 10000, k słow ze znakow ASCII (kod >= 63) o dlugosci <= 255
// wyjscie: odpowiedz na 4 pytania zakodowana w jednej liczbie
//          1 to odpowiedz twierdzaca, zapisywane od najmniej znaczacego bitu
//          dla wszystkich zestawow w jednej liczbie (cztery bity = jeden zestaw slow)

// czy w danym zestawie jest slowo:
// 1) z którego da się ułożyć każde inne słowo z zestawu
// 2) które da się ułożyć z każdego innego słowa z zestawu
// 3) którego nie da się ułożyć z żadnego innego słowa z zestawu
// 4) z którego nie da się ułożyć żadnego innego słowa z zestawu

#define MAX_WORD_LEN 255
#define CHARS_RANGE 64 // from 63 until 126
typedef unsigned long long ull;

ull analyse_wordset(int k, int chars_freq[][CHARS_RANGE]);
bool can_form(int word1[CHARS_RANGE], int word2[CHARS_RANGE]);

int main(void)
{
    // wczytanie liczby zestawow
    int n;
    scanf("%d", &n);

    // przeanalizowanie wszystkich zestawow
    ull ans = 0; int k;
    for (int set_idx = 0; set_idx < n; set_idx++)
    {
        // dla kazdego slowa zliczenie roznych znakow
        scanf("%d", &k);
        char word[MAX_WORD_LEN]; 
        int chars_freq[k][CHARS_RANGE];

        for (int i = 0; i < k; i++)
        {
            // wyzerowanie tablicy na liczbe wystapien znakow
            memset(chars_freq[i], 0, CHARS_RANGE * sizeof(int));

            scanf("%s", word);
            int len_word = strlen(word);
            for (int j = 0; j < len_word; j++)
            {
                // zwiekszenie licznika danego znaku
                chars_freq[i][(word[j] - '?')]++;
            }
            //printf("licznik dla slowa %s\n", word);
            //for(int k = 0; k < CHARS_RANGE; k++) printf("%d ", chars_freq[i][k]);
            //printf("\n");
        }

        // znalezienie odpowiedzi na cztery pytania
        ull flags = analyse_wordset(k, chars_freq);

        // przesuniecie bitowe o cztery pozycje w lewo w stosunku do poprzedniej odpowiedzi
        // operacja or dopisuje flagi do wyniku
        ans |= (flags << (4 * set_idx));

    }
    printf("%llu\n", ans);
    return 0;
}


// czy w danym zestawie jest slowo:
// 1) z którego da się ułożyć każde inne słowo z zestawu
// 2) które da się ułożyć z każdego innego słowa z zestawu
// 3) którego nie da się ułożyć z żadnego innego słowa z zestawu
// 4) z którego nie da się ułożyć żadnego innego słowa z zestawu
ull analyse_wordset(int k, int chars_freq[][CHARS_RANGE])
{
    ull flags = 0;
            
    // z ktorego da sie ulozyc kazde inne
    for (int i = 0; i < k; i++)
    {
        bool forms_all = true;
        for (int j = 0; j < k; j++)
        {
            if (i != j && !can_form(chars_freq[i], chars_freq[j]))
                {
                    forms_all = false;
                    break;
                }
        }
        if (forms_all)
        {
            flags |= 1U;
            break;
        }
    }

    // ktore da sie ulozyc z kazdego innego
    for (int i = 0; i < k; i++)
    {
        bool formed_from_all = true;
        for (int j = 0; j < k; j++)
        {
            if (i != j && !can_form(chars_freq[j], chars_freq[i]))
                {
                    formed_from_all = false;
                    break;
                }
        }
        if (formed_from_all)
        {
            flags |= (1U << 1);
            break;
        }
    }

    // ktore nie da sie ulozyc z zadnego innego
    for (int i = 0; i < k; i++)
    {
        bool not_formed_from_any = true;
        for (int j = 0; j < k; j++)
        {
            if (i != j && can_form(chars_freq[j], chars_freq[i]))
                {
                    not_formed_from_any = false;
                    break;
                }
        }
        if (not_formed_from_any)
        {
            flags |= (1U << 2);
            break;
        }
    }

    // z ktore nie da sie ulozyc zadnego innego
    for (int i = 0; i < k; i++)
    {
        bool forms_none = true;
        for (int j = 0; j < k; j++)
        {
            if (i != j && can_form(chars_freq[i], chars_freq[j]))
                {
                    forms_none = false;
                    break;
                }
        }
        if (forms_none)
        {
            flags |= (1U << 3);
            break;
        }
    }

    return flags;
}

// sprawdza czy z slowa word1 mozna stworzyc slowo word2
bool can_form(int word1[CHARS_RANGE], int word2[CHARS_RANGE])
{
    for (int i = 0; i < CHARS_RANGE; i++)
    {
        if (word1[i] < word2[i]) return false;
    }

    return true;
}