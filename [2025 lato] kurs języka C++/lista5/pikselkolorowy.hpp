
#pragma once
#include "kolor.hpp"
#include "piksel.hpp"
using namespace std;

class pikselkolorowy : public piksel, private kolor
{
public:
    pikselkolorowy(int x = 0, int y = 0, ushort r = 0, ushort g = 0, ushort b = 0)
    : piksel(x, y), kolor(r, g, b) {};

    void move(int dx, int dy)
    {
        int new_x = get_x() + dx;
        int new_y = get_y() + dy;

        piksel::check_range(new_x, new_y);
        set_xy(new_x, new_y);
    }
    
    friend ostream& operator << (ostream &wy, const pikselkolorowy &p);
};

ostream& operator << (ostream &wy, const pikselkolorowy &p)
{
    wy << "piksel(" << p.get_x() << ", " << p.get_y() << ")rgb(" << p.get_r() << ", " << p.get_g() << ", " << p.get_b() << ")" << '\n';
    return wy;
} 