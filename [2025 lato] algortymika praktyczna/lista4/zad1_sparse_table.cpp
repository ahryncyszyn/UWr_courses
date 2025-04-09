
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void precompute_answers(vector<vector<int>> &sparse_table, int N)
{
    // sparse_table[i][j] to zakres [j, j + 2^i - 1]
    int LOGN = static_cast<int>(log2(N)) + 1;
    for (int i = 1; i <= LOGN; i++)
    {
        for (int j = 0; j + (1 << i) <= N; j++)
        {
            // [j, j + 2^i - 1] = [j,  j + 2^(i-1) - 1] + [j + 2^(i-1), j + 2^i - 1]
            sparse_table[i][j] = min(sparse_table[i-1][j], 
                                     sparse_table[i-1][j + (1 << (i - 1))]);
        }
    }
}

int find_min_num(vector<vector<int>> &sparse_table, int a, int b)
{
    //           count leading zeros
    int len = 32 - __builtin_clz(b - a + 1) - 1;
    return min(sparse_table[len][a], sparse_table[len][b - (1 << len) + 1]);
}

// zloz. czas: O(N*log(N) + Q)
int main()
{
    int N, Q;
    cin >> N >> Q;
    int LOGN = static_cast<int>(log2(N)) + 1;

    vector<vector<int>> sparse_table(LOGN, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        cin >> sparse_table[0][i];
    }

    precompute_answers(sparse_table, N);

    int a, b;
    for (int i = 0; i < Q; i++)
    {
        cin >> a >> b;
        cout << find_min_num(sparse_table, --a, --b) << '\n';
    }
}