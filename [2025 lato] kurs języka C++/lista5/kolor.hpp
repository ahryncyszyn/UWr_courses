#pragma once
#include <iostream>
#include <stdexcept>

typedef unsigned short ushort;

class kolor
{
    ushort r, g, b;

public:
    kolor() : r(0), g(0), b(0) {};

    kolor(ushort new_r, ushort new_g, ushort new_b)
    {
        if ( new_r > 255 || new_g > 255 || new_b > 255)
        {
            throw std::out_of_range("kolory moga byc tylko w zakresie 0-255");
        }
        r = new_r;
        g = new_g;
        b = new_b;
    }

    ushort get_r() const { return r; }
    ushort get_g() const { return g; }
    ushort get_b() const { return b; }

    void set_r(ushort new_r) 
    {
        if (new_r > 255) throw std::out_of_range("kolory moga byc tylko w zakresie 0-255");
        r = new_r; 
    }
    void set_g(ushort new_g) 
    { 
        if (new_g > 255) throw std::out_of_range("kolory moga byc tylko w zakresie 0-255");
        g = new_g; 
    }
    void set_b(ushort new_b) 
    { 
        if (new_b > 255) throw std::out_of_range("kolory moga byc tylko w zakresie 0-255");
        b = new_b; 
    }

    void make_darker() 
    {
        r = 0.75 * r;
        g = 0.75 * g;
        b = 0.75 * b;
    }

    void make_lighter() 
    {
        ushort dr = 0.25 * r;
        ushort dg = 0.25 * g;
        ushort db = 0.25 * b;
        r = ((r + dr) > 255) ? 255 : r + dr;
        g = ((g + dg) > 255) ? 255 : g + dg;
        b = ((b + db) > 255) ? 255 : b + db;
    }

    static kolor polacz(const kolor &k1, const kolor &k2) 
    {
        ushort red = (k1.r + k2.r) / 2;
        ushort green = (k1.g + k2.g) / 2;
        ushort blue = (k1.b + k2.b) / 2;
        return kolor(red, green, blue);
    }

    friend std::ostream& operator << (std::ostream &wy, const kolor &k);
};

std::ostream& operator<< (std::ostream &wy, const kolor &k)
{
    wy << "rgb(" << k.r << ", " << k.g << ", " << k.b << ")" << '\n';
    return wy;
}
