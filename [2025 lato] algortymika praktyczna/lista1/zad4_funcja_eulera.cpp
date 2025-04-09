#include <iostream>
#include <vector>
using namespace std;

// phi(n) = n * (1 - 1/p1) * (1 - 1/p2) * ...
// phi(n) = (n - n/p) * ...
// phi(n) = n/p * (p - 1) * ...
void calculate_phi(vector<int> &phi, int max_num)
{
    for (int i = 0; i <= max_num; i++)
    {
        phi[i] = i;
    }

    for (int i = 2; i <= max_num; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j <= max_num; j += i)
            {
                phi[j] = (phi[j] / i) * (i - 1);
            }
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

    vector<int> phi(max_num + 1, 0);
    calculate_phi(phi, max_num);

    for (int i = 0; i < N; i++)
    {
        cout << phi[nums[i]] << endl;
    }
    return 0;
}