#include <stdio.h>

int minKoszt(int n, int a[][n])
{
    for (int j = 1; j < n; j++)
    {
        a[0][j] += a[0][j-1];
    }

    for (int i = 1; i < n; i++)
    {
        a[i][0] += a[i-1][0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            a[i][j] += (a[i-1][j] < a[i][j-1]) ? a[i-1][j] : a[i][j-1];
        }
    }

    return a[n-1][n-1];
}

int main()
{
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int res = minKoszt(3, a);
    printf("%d\n", res);

}