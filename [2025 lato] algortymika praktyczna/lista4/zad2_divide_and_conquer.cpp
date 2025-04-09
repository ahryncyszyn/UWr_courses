
#include <iostream>
#include <vector>
using namespace std;

void divide_and_conquer(vector<int> &nums, vector<pair<pair<int, int>, int>> &queries,
                        vector<int> &results, int a, int b)
{
    if (a == b)
    {
        for (auto query : queries)
        {
            if (query.first.first == a && query.first.second == b)
            {
                results[query.second] = nums[a];
            }
        }
        return;
    }

    int mid = (a + b) / 2;

    // przechowuje min(nums[i] do nums[mid])
    vector<int> left_min(b - a + 1);
    left_min[mid - a] = nums[mid];
    for (int i = mid - 1; i >= a; i--)
    {
        left_min[i - a] = min(nums[i], left_min[i - a + 1]);
    }
    // przechowuje min(nums[mid + 1] do nums[i])
    vector<int> right_min(b - a + 1);
    right_min[mid - a + 1] = nums[mid + 1];
    for (int i = mid + 2; i <= b; i++)
    {
        right_min[i - a] = min(nums[i], right_min[i - a - 1]);
    }

    // rozdzielanie zapytan
    vector<pair<pair<int, int>, int>> left_queries;
    vector<pair<pair<int, int>, int>> right_queries;
    for (auto query : queries)
    {
        if (query.first.second <= mid)
        {
            left_queries.push_back(query); 
        }
        else if (query.first.first > mid)
        {
            right_queries.push_back(query);
        }
        // dla zapytan zaczynajacych sie przed mid i konczacych za mid mamy wynik
        else results[query.second] = min(left_min[query.first.first - a], 
                                         right_min[query.first.second - a]);
    }

    divide_and_conquer(nums, left_queries, results, a, mid);
    divide_and_conquer(nums, right_queries, results, mid + 1, b);
}

// zloz. czas. O(N*log(N) + Q)
int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    int a, b;
    vector<pair<pair<int, int>, int>> queries(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> a >> b;
        queries[i] = {{a - 1, b - 1}, i};
    }

    vector<int> results(Q);
    divide_and_conquer(nums, queries, results, 0, N - 1);
    for (int i = 0; i < Q; i++)
    {
        cout << results[i] << "\n";
    }
}