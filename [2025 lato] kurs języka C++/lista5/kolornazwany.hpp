#pragma once
#include <stdexcept>
#include "kolor.hpp"
#include <string>
using namespace std;

typedef unsigned short ushort;

class kolornazwany : public virtual kolor 
{
    string name;

public:
    kolornazwany() : kolor(), name("") {};

    kolornazwany(ushort r, ushort g, ushort b, const std::string &new_name)
    : kolor(r, g, b)
    {
        set_name(new_name);
    }

    void set_name(const std::string &new_name)
    {
        for (char c : new_name)
        {
            if (!islower(c))
            {
                throw invalid_argument("nazwa koloru powinna sie skladac tylko z malych liter alfabetu angielskiego");
            } 
        }
        name = new_name;
    }

    std::string get_name() const
    {
        return name;
    }

    friend std::ostream& operator << (std::ostream &wy, const kolornazwany &k);
};

std::ostream& operator<< (std::ostream &wy, const kolornazwany &k)
{
    wy << k.name << "(" << k.get_r() << ", " << k.get_g() << ", " << k.get_b() << ")" << '\n';
    return wy;
}