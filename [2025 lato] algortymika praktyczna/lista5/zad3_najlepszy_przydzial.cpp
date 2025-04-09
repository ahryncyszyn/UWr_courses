#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int find_max_profit(vector<vector<int>> &profit, int N)
{
    // przechowuje maksymalna sume zysku dla i pracownikow
    vector<int> dp(1 << N, 0);
    for (unsigned int mask = 0; mask < (1 << N); mask++)
    {
        // liczba zapalonych bitow w masce
        int people = __builtin_popcount(mask);
        
        // przydzielanie nowego pracownika do maszyny
        for (int task = 0; task < N; task++)
        {
            if ((mask & (1 << task)) == 0)
            {
                int new_mask = (mask | (1 << task));
                dp[new_mask] = max(dp[new_mask],
                                   dp[mask] + profit[people][task]);
            }
        }
    }
    return dp[(1 << N) - 1];
}

// zloz. czas: O(n*2^n)
int main()
{
    int N;
    cin >> N;

    // kazdy wiersz opisuje zysk danego pracownika na jednym z N stanowisk
    vector<vector<int>> profit(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> profit[i][j];
        }
    }

    cout << find_max_profit(profit, N);
}