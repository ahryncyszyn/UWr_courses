#include "wyrazenie.hpp"

namespace obliczenia {

class zmienna : public wyrazenie
{
    string nazwa;
    static vector<pair<string, int>> zmienne;

public:
    zmienna(string n) : nazwa(n) {};
    int oblicz() override
    {
        for (auto it = zmienne.begin(); it != zmienne.end(); it++)
        {
            if (it -> first == nazwa) return it -> second;
        }
        throw runtime_error("zmienna niezdefiniowana: " + nazwa);
    }
    string zapis() override { return nazwa; };
    int priorytet() override { return 100; };
    ~zmienna() {};

    static void add_variable(string name, int value)
    {
        zmienne.push_back(pair<string, int>(name, value));
    }
    static void remove_variable(string name)
    {
        for (auto it = zmienne.begin(); it != zmienne.end(); it++)
        {
            if (it -> first == name)
            {
                zmienne.erase(it);
                break;
            }
        }
    }
    static void modify_variable(string name, int value)
    {
        for (auto it = zmienne.begin(); it != zmienne.end(); it++)
        {
            if (it -> first == name)
            {
                it -> second = value;
                break;
            }
        }
    }
};

}