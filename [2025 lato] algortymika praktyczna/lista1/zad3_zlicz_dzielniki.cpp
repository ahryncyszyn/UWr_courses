#include <iostream>
#include <vector>
using namespace std;

void count_all_divisors(vector<int> &sieve, int max_num)
{
    for (int i = 2; i <= max_num; i++)
    {
        for (int j = i; j <= max_num; j += i)
        {
            sieve[j]++;
        }
    }
}

// zloz. czas: O(n*log(n))
int main()
{
    int N, num, max_num = 0;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        nums[i] = num;
        if (num > max_num) max_num = num;
    }

    vector<int> sieve(max_num + 1, 1);
    count_all_divisors(sieve, max_num);

    for (int i = 0; i < N; i++)
    {
        cout << sieve[nums[i]] << endl;
    }
    return 0;
}