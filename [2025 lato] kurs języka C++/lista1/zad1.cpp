// Aleksandra Hryncyszyn, 353636

#include <iostream>
#include <vector>
#include <string>
#include <cstdint> // wymagane dla windowsa
using namespace std;

vector<int64_t> prime_factorization(int64_t num)
{

    vector<int64_t> factors;

    if (num == -1 || num == 0 || num == 1)
    {
        factors.push_back(num);
        return factors;
    }
    
    if (num < 0)
    {
        factors.push_back(-1);
        num = -num;
    }

    while (num % 2 == 0)
    {
        factors.push_back(2);
        num /= 2;
    }

    int64_t num_sqrt = sqrt(num);
    for (int64_t div = 3; div <= num_sqrt; div += 2)
    {
        while (num % div == 0)
        {
            factors.push_back(div);
            num /= div;
        }
    }

    if (num > 2) factors.push_back(num);
    return factors;
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cerr << "Poprawne uzycie programu: nazwa_programu liczba1 liczba2 ..." << endl;
        return 1;
    }

    // wczytanie wszystkich liczb
    vector<int64_t> nums;
    for (int i = 1; i < argc; i++)
    {
        // konwertowanie liczby
        try
        {
            nums.push_back(stoll(argv[i]));
        }
        catch(invalid_argument &e)
        {
            cerr << e.what() << " - argument powinien byc liczba calkowita" << '\n';
            return 1;
        }
    }

    for (int64_t num : nums)
    {
        // rozkład na czynniki pierwsze
        vector<int64_t> factors = prime_factorization(num);

        // wypisywanie wyniku
        cout << num << " = ";
        for (unsigned long long i = 0; i < factors.size(); i++)
        {
            cout << factors[i];
            if (i != factors.size() - 1) cout << " * ";
        }
        cout << "\n";
    }
}