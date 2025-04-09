#include <iostream>
#include <vector>

int is_free(int col, int row, std::vector<int> &positions)
{
    for (int i = 0; i < col; i++)
    {
        if (positions[i] == row || positions[i] - i == row - col 
            || positions[i] + i == row + col) return 0;
    }
    return 1;
}

void count_queens_solutions(int col, int N, std::vector<int> &positions, int &count)
{
    if (col == N)
    {
        count++;
        return;
    }

    for (int row = 0; row < N; row++)
    {
        if (is_free(col, row, positions))
        {
            positions[col] = row;
            count_queens_solutions(col + 1, N, positions, count);
        }
    }
}

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> positions(N);

    int count = 0;
    count_queens_solutions(0, N, positions, count);
    std::cout << count;
    return 0;
}