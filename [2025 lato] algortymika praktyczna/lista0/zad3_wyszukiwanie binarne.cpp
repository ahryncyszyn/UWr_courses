#include <iostream>
#include <vector>

int bin_search(const std::vector<int>& numbers, int x)
{
    int left = 0, right = numbers.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (numbers[mid] == x) return mid + 1; 
        else if (numbers[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// zlozonosc czas: O(M*log(N))
int main()
{
    int N, M, x;
    std::cin >> N;
    std::vector<int> numbers(N);

    for (int i = 0; i < N; i++)
    {
        std::cin >> numbers[i];
    }

    std::cin >> M;
    for (int i = 0; i < M; i++)
    {
        std::cin >> x;
        std::cout << bin_search(numbers, x) << std::endl;
    }
    return 0;
}

