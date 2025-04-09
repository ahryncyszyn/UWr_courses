#include "wektor.hpp"

wektor::wektor() : dx(0), dy(0) {};

wektor::wektor(double new_dx, double new_dy) : dx(new_dx), dy(new_dy) {};

wektor::~wektor() {};

double wektor::getDx() const
{
    return dx;
}

double wektor::getDy() const
{
    return dy;
}