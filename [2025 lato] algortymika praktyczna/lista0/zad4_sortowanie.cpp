#include <iostream>
#include <vector>

void merge(std::vector<int> &numbers, int left, int mid, int right)
{
    int len1 = mid - left + 1;
    int len2 = right - mid;

    std::vector<int> leftvec(len1), rightvec(len2);
    for (int i = 0; i < len1; i++) leftvec[i] = numbers[left + i];
    for (int i = 0; i < len2; i++) rightvec[i] = numbers[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2)
    {
        if (leftvec[i] <= rightvec[j]) numbers[k++] = leftvec[i++];
        else numbers[k++] = rightvec[j++];
    }

    while (i < len1) numbers[k++] = leftvec[i++];
    while (j < len2) numbers[k++] = rightvec[j++];
}

void mergesort(std::vector<int> &numbers, int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergesort(numbers, left, mid);
    mergesort(numbers, mid + 1, right);
    merge(numbers, left, mid, right);
}

// zlozonosc czas: O(n*log(n))
int main()
{
    int N;
    std::cin >> N;

    std::vector<int> numbers(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> numbers[i];
    }

    mergesort(numbers, 0, N - 1);

    for (int i = 0; i < N; i++)
    {
        std::cout << numbers[i] << " ";
    }
    return 0;
}