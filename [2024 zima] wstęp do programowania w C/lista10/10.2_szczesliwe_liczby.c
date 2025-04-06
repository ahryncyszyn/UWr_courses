
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Należy wczytać liczby x, y i policzyć, ile jest liczb w przedziale [x,y] takich, że jednocześnie:
// 1 - suma pierwszych czterech cyfr jest podzielna przez 22,
// 2 - suma cyfr na pozycjach parzystych jest większa od sumy cyfr na pozycjach nieparzystych o przynajmniej 19,
// 3 - liczba zawiera trzy sąsiednie cyfry '3' i dwie sąsiednie cyfry '7'.

#define MAX_DIGITS 16 // maksymalna liczba cyfr dla zakresu [0, 10^13]

bool check_conditions(char curr_num[]);
bool check_condition1(char num[]);
bool has_3_threes(char curr_num[]);

void count_lucky_nums(long long curr_num, int pos, 
                        int sum_odd, int sum_even, int three_count, int seven_count,
                        int max_len, long long x, long long y, int* count)
{
    if (curr_num > y) return;

    // jezeli pierwsze 4 cyfry nie spelniaja warunku 1, liczba nie jest szczesliwa
    if (pos >= 4 && !check_condition1(curr_num)) return;


    if (pos >= min_len && check_condition1(curr_num) && check_conditions(curr_num)) 
    {
        (*count)++;
    }
    
    if (pos == max_len) return;

    // dodawanie kolejnych cyfr
    // wartosc pierwszej cyfry ograniczona przez min i maks liczby
    for (int digit = 0; digit <= 9; digit++)
    {
        // jezeli nie ma jeszcze trzech trojek a jest koncowka liczby to trzeba dodac 3
        if (pos >= max_len - 3 && !has_3_threes(curr_num) && digit != 3) continue;

        long long new_num = curr_num * 10 + digit;
        count_lucky_nums(new_num, pos + 1, max_len, x, y, count);
    }
}

int main()
{
    // wczytanie zakresu liczb
    long long x, y;
    scanf("%lld%lld", &x, &y);

    if (y < 1777073339)
    {
        printf("0"); 
        return 1;
    }

    // zlicza liczbe cyfr w y
    int max_len = snprintf(NULL, 0, "%lld", y);

    int count = 0;
    count_lucky_nums(0, 0, max_len, x, y, &count);
    printf("%d", count);

    return 1;
}

bool has_3_threes(char num[])
{
    int len = strlen(num);
    for (int i = 0; i < len - 2; i++) 
    {
        if (num[i] == '3' && num[i + 1] == '3' && num[i + 2] == '3') 
        {
            return true;
        }
    }
    return false;
}

bool check_condition1(char num[])
{
    int len = strlen(num);

    // suma pierwszych czterech cyfr podzielna przez 22
    if (len < 4) return false;
    int first_four_sum = 0;
    for (int i = 0; i < 4; i++) 
    {
        first_four_sum += num[i] - '0';
    }
    if (first_four_sum % 22 != 0) return false;
    return true;
}

bool check_conditions(char num[])
{
    int len = strlen(num);

    // suma cyfr na pozycjach parzystych większa od nieparzystych o co najmniej 19
    int even_sum = 0, odd_sum = 0;
    for (int i = 0; i < len; i++) 
    {
        if ((i + 1) % 2 == 0) { 
            even_sum += num[i] - '0';
        } else 
        {
            odd_sum += num[i] - '0';
        }
    }
    if (even_sum - odd_sum < 19) return false;

    // trzy sąsiednie cyfry '3' i dwie sąsiednie cyfry '7'
    bool has_three_3s = false, has_two_7s = false;
    for (int i = 0; i < len - 2; i++) 
    {
        if (num[i] == '3' && num[i + 1] == '3' && num[i + 2] == '3') 
        {
            has_three_3s = true;
        }
    }
    for (int i = 0; i < len - 1; i++)
    {
        if (num[i] == '7' && num[i + 1] == '7') 
        {
            has_two_7s = true;
        }
    }
    return has_three_3s && has_two_7s;
}