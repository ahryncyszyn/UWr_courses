#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
typedef unsigned long long ull;

vector<int> sequence1;
vector<int> sequence2;
ull hashes[1000001];
vector<ull> prefix1;
vector<ull> prefix2;

void calculate_hashes(int N)
{
    int x;
    srand(time(0) + (long long)&x);
    for (int i = 0; i < 1000001; i++)
    {
        hashes[i] = ((ull)rand() << 32) ^ rand();
    }

    prefix1.resize(N + 1);
    prefix2.resize(N + 1);
    prefix1[0] = 0;
    prefix2[0] = 0;
    for (int i = 0; i < N; i++) 
    {
        prefix1[i + 1] = prefix1[i] ^ hashes[sequence1[i]];
        prefix2[i + 1] = prefix2[i] ^ hashes[sequence2[i]];
    }
}

void check_elements(int l1, int r1, int l2, int r2)
{
    ull hash1 = prefix1[r1] ^ prefix1[l1 - 1];
    ull hash2 = prefix2[r2] ^ prefix2[l2 - 1];
    if (hash1 == hash2) cout << "TAK\n";
    else cout << "NIE\n";
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    sequence1.resize(N);
    sequence2.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> sequence1[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> sequence2[i];
    }
    calculate_hashes(N);
    int l1, r1, l2, r2;
    for (int i = 0; i < Q; i++)
    {   
        cin >> l1 >> r1 >> l2 >> r2;
        check_elements(l1, r1, l2, r2);
    }
}