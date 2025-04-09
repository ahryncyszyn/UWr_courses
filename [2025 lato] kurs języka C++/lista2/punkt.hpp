#ifndef punkt_hpp
#define punkt_hpp

#include "wektor.hpp"
#include "prosta.hpp"
#include <iostream>
#include <cmath>

class punkt
{
    double x, y;

public:
    punkt();
    punkt(double x, double y);
    ~punkt();

    double getX() const;
    double getY() const;

    void setX(double new_x);
    void setY(double new_y);

    void translacja(wektor v);
    void obrot(punkt p, double kat_stopnie);
    void symetria_srodkowa(punkt p);
    void symetria_osiowa(prosta p);
    void print();
};

double odleglosc(const punkt& p1, const punkt& p2);

#endif