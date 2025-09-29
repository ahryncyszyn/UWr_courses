
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long double ldouble;

struct point
{
    ldouble x, y;
};

ldouble vec_prod(point &a, point &b)
{
    return b.x * a.y - a.x * b.y;
}

ldouble calculate_area(vector<point> &points, int N)
{
    ldouble area = 0;
    for (int i = 0; i < (N - 1); i++)
    {
        area += vec_prod(points[i], points[i + 1]);
    }
    area += vec_prod(points[N - 1], points[0]);
    return abs(area) / 2;
}

int main()
{
    int N;
    cin >> N;

    vector<point> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    printf("%.1Lf", calculate_area(points, N));
}