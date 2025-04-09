#ifndef punkt_hpp
#define punkt_hpp

#include <iostream>
using namespace std;

class punkt
{
    double x, y;

    public:
    punkt(double new_x, double new_y) : x(new_x), y(new_y) {};
    punkt() : x(0), y(0) {};
    ~punkt() {};

    double getX() const { return x; };
    double getY() const { return y; };

    void setX(double new_x) { x = new_x; };
    void setY(double new_y) { y = new_y; };

    void print()
    {
        cout << "(" << x << ", " << y << ") ";
    }
};

#endif