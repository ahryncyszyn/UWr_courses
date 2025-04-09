#include <iostream>
using namespace std;

// a * k + b * l = gcd(a, b)
// b * k + (a % b) * l = gcd(a, b)
// b * k + (a - a/b * b) * l = gcd(a, b)
// a * l + (k - a/b * l) * b = gcd(a, b)
int extended_gcd(int a, int b, int& k, int& l)
{
    if (b == 0)
    {
        k = 1;
        l = 0;
        return a;
    }

    int prev_k, prev_l, gcd;
    gcd = extended_gcd(b, a%b, prev_k, prev_l);

    k = prev_l;
    l = prev_k - (a/b) * prev_l;
    return gcd;
}

// zlozonsc czas: O(n*log(min(a, b)))
int main()
{
    int N;
    cin >> N;

    int a, b, k, l, gcd;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        gcd = extended_gcd(a, b, k, l);
        cout << k << " " << l << " " << gcd << endl;
    }
    return 0;
}