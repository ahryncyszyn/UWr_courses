
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
typedef long double ld;

struct point
{
    ld x, y;
    ld angle;
};

int main()
{
    point q;
    cin >> q.x;
    q.y = 0;

    int N;
    cin >> N;

    vector<point> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
        points[i].angle = points[i].y / (points[i].x - q.x);
    }

    sort(points.begin(), points.end(), [](point &a, point &b) { return a.angle < b.angle; });

    int unique = 0;
    ld prev = -1e20;
    for (int i = 0; i < N; i++)
    {
        if (points[i].angle > prev)
        {
            unique++;
            prev = points[i].angle;
        }
    }
    cout << unique;
}