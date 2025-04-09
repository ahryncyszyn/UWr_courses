#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int stripe_width;
struct point
{
    int x, y, idx;
};

// zwraca true jezeli a < b
bool comp(const point &a, const point &b)
{
    int stripe_idx_a = a.x / stripe_width;
    int stripe_idx_b = b.x / stripe_width;

    if (stripe_idx_a < stripe_idx_b) return true;
    if (stripe_idx_a > stripe_idx_b) return false;

    // paski o parzystych indeksach porzadkujemy od gory w dol
    if (stripe_idx_a % 2 == 0)
    {
        return (a.y > b.y);
    }
    // paski o nieparzystyczh indeksach od dolu w gore
    else return (a.y < b.y);
}

int main()
{
    int N;
    cin >> N;

    vector<point> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
        points[i].idx = i + 1;
    }

    stripe_width = static_cast<int>(ceil(sqrt(N)));
    sort(points.begin(), points.end(), comp);

    for (int i = 0; i < N; i++)
    {
        cout << points[i].idx << " ";
    }

    return 0;
}