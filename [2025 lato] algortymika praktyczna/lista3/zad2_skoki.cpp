#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

// złożoność czas: O(sqrt(N))
// maksymalnie N / jump iteracji
// gdzie jump to minimalnie sqrt(N)
ll count_sum(vector<int> &nums, int start, int jump)
{
    ll sum = 0;
    for (int i = start; i < nums.size(); i += jump)
    {
        sum += nums[i];
    }
    return sum;
}

// zlożoność czas: O(Nsqrt(N))
// zewnętrzna pętla ma sqrt(N) iteracji
// wewnętrzna ma jump * N/jump, więc N
void preprocess(vector<int> &nums, int N, vector<vector<ll>> &preprocessed_sums)
{
    int square = static_cast<int>(ceil(sqrt(N)));
    for (int jump = 1; jump < square; jump++)
    {
        preprocessed_sums[jump].resize(N);
        for (int start = 0; start < jump; start++)
        {
            ll curr_sum = 0;
            for (int i = N - 1 - start; i >= 0; i -= jump)
            {
                curr_sum += nums[i];
                preprocessed_sums[jump][i] = curr_sum;
            }
        }
    }
}

// złożoność czas: O(N + Nsqrt(N) + Qsqrt(N))
// = O(N(sqrt(N)) + Q(sqrt(N)))
int main()
{
    int N, Q, start, jump;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++) 
    {
        cin >> nums[i];
    }

    int square = static_cast<int>(ceil(sqrt(N)));
    vector<vector<ll>> preprocessed_sums(square);
    preprocess(nums, N, preprocessed_sums);

    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        cin >> start >> jump;
        if (jump < square) 
        {
            cout << preprocessed_sums[jump][--start] << '\n';
        }
        else cout << count_sum(nums, --start, jump) << '\n';
    }
    return 0;
}