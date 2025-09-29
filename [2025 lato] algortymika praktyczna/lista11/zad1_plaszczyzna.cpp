
#include <iostream>
#include <vector>
typedef long long ll;
typedef struct point point;
using namespace std;

struct point
{
    ll x;
    ll y;

    point& operator-=(point& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    ll vec_prod(point& b)
    {
        return b.x * y - x * b.y;
    }
};

int main()
{
    int T;
    cin >> T;

    point p1, p2, p3;
    for (int i = 0; i < T; i++)
    {
        cin >> p1.x >> p1.y 
            >> p2.x >> p2.y
            >> p3.x >> p3.y;

        p2 -= p1;
        p3 -= p1;

        ll prod = p2.vec_prod(p3);
        if (prod == 0) cout << "TOUCH\n";
        else if (prod > 0) cout << "RIGHT\n";
        else cout << "LEFT\n";
    }
}