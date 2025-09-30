#pragma once
#include <stdexcept>
#include "kolor.hpp"

typedef unsigned short ushort;

class kolortransparentny: public virtual kolor
{
    ushort alfa;

public:
    kolortransparentny() : kolor(), alfa(0) {};

    kolortransparentny(ushort r, ushort g, ushort b, ushort new_alfa) 
    : kolor(r, g, b), alfa(new_alfa)
    {
        if (new_alfa > 255) throw std::out_of_range("alfa moze byc tylko w zakresie 0-255");
    }

    ushort get_alfa() { return alfa; }

    void set_alfa(ushort new_alfa)
    {
        if (new_alfa > 255) throw std::out_of_range("alfa moze byc tylko w zakresie 0-255");
        alfa = new_alfa;
    }

    friend std::ostream& operator << (std::ostream &wy, kolortransparentny &k);
};

std::ostream& operator<< (std::ostream &wy, kolortransparentny &k)
{
    wy << "rgba(" << k.get_r() << ", " << k.get_g() << ", " << k.get_b() << ", " << k.alfa <<  ")" << '\n';
    return wy;
}
