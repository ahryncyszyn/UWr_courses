#pragma once
#include "kolor.hpp"
#include "kolornazwany.hpp"
#include "kolortansparentny.hpp"
#include <stdexcept>
#include <string>
using namespace std;

typedef unsigned short ushort;

class kolortransnaz : public kolortransparentny, public kolornazwany 
{
public:
    kolortransnaz() : kolortransparentny(), kolornazwany() {};

    kolortransnaz(ushort r, ushort g, ushort b, ushort alfa, std::string &name)
    : kolor(r, g, b)
    {
        set_alfa(alfa);
        set_name(name);
    }

    friend std::ostream& operator << (std::ostream &wy, const kolortransnaz &k);
};

std::ostream& operator<< (std::ostream &wy, const kolortransnaz &k)
{
    wy << k.get_name() << "(" << k.get_r() << ", " << k.get_g() << ", " << k.get_b() << ")" << '\n';
    return wy;
}