#pragma once
#include "kolor.hpp"
#include "kolornazwany.hpp"
#include "kolortansparentny.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class piksel
{
    static const int screen_size_x = 1920;
    static const int screen_size_y = 1080;
    int x, y;

protected:
    void check_range(int _x, int _y)
    {
        if (_x < 0 || _x >= screen_size_x || _y < 0 || _y >= screen_size_y) 
        {
            throw std::out_of_range("Wspolrzedne wykraczaja poza ekran.");
        }
    }

public:
    piksel(int _x = 0, int _y = 0)
    {
        check_range(_x, _y);
        x = _x;
        y = _y;
    }

    int get_x() const { return x; };
    int get_y() const { return y; };

    void set_x(int _x)
    {
        check_range(_x, y);
        x = _x;
    }

    void set_y(int _y)
    {
        check_range(x, _y);
        y = _y;
    }

    void set_xy(int _x, int _y)
    {
        check_range(_x, _y);
        x = _x;
        y = _y;
    }

    int dist_from_left_side() { return x; }
    int dist_from_right_side() { return (screen_size_x - x); }
    int dist_from_top_side() { return y; }
    int dist_from_bottom_side() { return (screen_size_y - y); }

    static double distance(piksel &p1, piksel &p2)
    {
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }

    static double distance(piksel *p1, piksel *p2)
    {
        if (!p1 || !p2) throw invalid_argument("wskaznik na piksel jest pusty");
        int dx = p1->x - p2->x;
        int dy = p1->y - p2->y;
        return sqrt(dx * dx + dy * dy);
    }

    friend ostream& operator << (ostream &wy, const piksel &p);
};

ostream& operator << (ostream &wy, const piksel &p)
{
    wy << "piksel(" << p.x << ", " << p.y << ")" << '\n';
    return wy;
} 