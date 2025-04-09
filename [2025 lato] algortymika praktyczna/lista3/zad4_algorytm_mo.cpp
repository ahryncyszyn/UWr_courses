#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ustalamy limit x, bo rozmiar tablicy liczb to maksymalnie 1e5 
const int MAXN = 1e5;
int freq[MAXN];
int block_size;
int ans = 0;
struct query 
{
    int p, k, idx;
};

// sortuje zapytania najpierw ze wzgledu na poczatek zakresu potem ze wzgledu na koniec
bool comp(const query &a, const query &b)
{
    int block_a = a.p / block_size;
    int block_b = b.p / block_size;

    if (block_a != block_b) return block_a < block_b;
    return a.k < b.k;
}

void remove(vector<int> &nums, int idx)
{
    int x = nums[idx];
    if (x >= MAXN) return;

    if (freq[x] == x) ans--;
    else if (freq[x] == x + 1) ans++;
    freq[x]--;
}

void add(vector<int> &nums, int idx)
{
    int x = nums[idx];
    if (x >= MAXN) return;

    if (freq[x] == x - 1) ans++;
    else if (freq[x] == x) ans--;
    freq[x]++;
}

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
    block_size = static_cast<int>(ceil(sqrt(N)));

    vector<query> queries(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> queries[i].p >> queries[i].k;
        queries[i].p--; queries[i].k--;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(), comp);

    int l = 0, r = -1;
    vector<int> answers(Q);
    for (auto query : queries)
    {
        while (r < query.k) add(nums, ++r);
        while (r > query.k) remove(nums, r--);
        while (l < query.p) remove(nums, l++);
        while (l > query.p) add(nums, --l);
        answers[query.idx] = ans;
    }

    for (int i = 0; i < Q; i++)
    {
        cout << answers[i] << "\n";
    }

    return 0;
}