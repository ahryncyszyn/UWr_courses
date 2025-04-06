
int count_digits(int number)
{
    if (number == 0) return 1;
    if (number < 0) number = -number;

    int res = 0;
    while (number > 0)
    {
        res += 1;
        number /= 10;
    }
    return res;
}

int reverse_number(int number)
{
    if (number == 0) return 0;
    int ujemna = 0;
    if (number < 0) 
    {
        number = -number;
        ujemna = 1;
    }

    int reversed = 0;
    while (number > 0)
    {
        reversed *= 10;
        reversed += number % 10;
        number /= 10;
    }
    return ujemna ? -reversed : reversed;
}

int digit_sum(int number)
{
    int sum = 0;
    if (number < 0) number = -number;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}
