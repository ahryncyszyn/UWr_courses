#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long double ld;

struct point
{
    ld x, y;
};

ld find_distance(point &q, point& p1, point& p2)
{
    // wyznaczanie parametrow prostej
    ld a = p2.y - p1.y;
    ld b = p1.x - p2.x;
    ld c = p1.y * p2.x - p1.x * p2.y;

    // wyznaczanie odleglosci z wzoru
    return fabs(a * q.x + b * q.y + c) / (sqrt(a * a + b * b));
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