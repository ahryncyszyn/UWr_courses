#include <iostream>

// NWD(a, b) = NWD(b, a % b) = NWD(b, r) = NWD(kb + r, b)
// zlozonosc czas: O(log(min(a, b)))
long long GCD(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    long long a, b;
    std::cin >> a >> b;
    std::cout << GCD(a, b);
    return 0;
}   