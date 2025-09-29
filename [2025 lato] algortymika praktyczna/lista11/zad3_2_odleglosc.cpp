#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long double ld;

struct point
{
    ld x, y;

    point& operator-=(point& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }
};

ld vec_prod(point &a, point &b)
{
    return b.x * a.y - a.x * b.y;
}

ld find_distance(point &q, point& p1, point& p2)
{
    p1 -= q;
    p2 -= q;

    return 2 * vec_prod(p1, p2) / sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

int main()
{
    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        point p1, p2, q;
        cin >> p1.x >> p1.y
            >> p2.x >> p2.y
            >> q.x >> q.y;
        
        cout << setprecision(10) << find_distance(q, p1, p2) << "\n";
    }
}