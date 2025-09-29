
#include <iostream>
#include <vector>
using namespace std;

struct point
{
    int x;
    int y;
};

vector<point> points;
vector<point> convex_hull;

int vec_prod(point &a, point &b)
{
    return b.x * a.y - a.x * b.y;
}

point& find_bottom_most(int N)
{
    point bottom = points[0];
    for (int i = 1; i < N; i++)
    {
        if ((points[i].y < bottom.y) || 
            (points[i].y == bottom.y && points[i].x < bottom.x))
        {
            bottom = points[i];
        }
    }
}

void find_convex_hull(int N)
{
    point p0 = find_bottom_most(N);
    // sortowanie katowe
    sort(points.begin(), points.end(), [](const point& a, const point& b)
    {
        // todo
    });

}

int main()
{
    int N;
    points.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    find_convex_hull(N);

}