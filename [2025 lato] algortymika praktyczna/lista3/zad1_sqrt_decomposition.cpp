#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

// zamienia liczbe na pozycji a na wartosc b
void update_value(vector<int> &nums, vector<ll> &blocks, int block_size, int a, int b)
{
    int block_idx = a / block_size;
    blocks[block_idx] += b - nums[a];
    nums[a] = b;
}

// oblicza sume zakresu nums[a, b] - O(sqrt(N))
ll range_sum(vector<int> &nums, vector<ll> &blocks, int block_size, int a, int b)
{
    ll sum = 0;
    for (int i = a; i <= b;)
    {
        // dodaje cały blok
        if (i % block_size == 0 && i + block_size - 1 <= b)
        {
            sum += blocks[i / block_size];
            i += block_size;
        }
        // dodaje pojedyncze liczby
        else sum += nums[i++];
    }
    return sum;
}

// zloz. czas. - O(Q*sqrt(N))
int main()
{
    // wczytanie dlugosci ciagu liczb oraz liczby zapytan
    int N, Q;
    cin >> N >> Q;

    // wczytywanie ciagu liczb
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // przetwarzanie liczb do formy blokowej
    int block_size = static_cast<int>(ceil(sqrt(N)));
    int blocks_count = N / block_size;
    if (blocks_count * block_size < N) blocks_count++;

    vector<ll> blocks(blocks_count, 0);
    for (int i = 0; i < N; i++)
    {
        int block_idx = i / block_size;
        blocks[block_idx] += nums[i];
    }

    // przetwarzanie zapytan
    int query, a, b;
    for (int i = 0; i < Q; i++)
    {
        cin >> query >> a >> b;
        if (query == 1) update_value(nums, blocks, block_size, --a, b);
        else if (query == 2) 
        {
            cout << range_sum(nums, blocks, block_size, --a, --b) << "\n";
        }
    }
    return 0;
}