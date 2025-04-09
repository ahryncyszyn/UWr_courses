#ifndef kolo_hpp
#define kolo_hpp

#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include <stdexcept>
#include <iostream>
#include <numbers>
#include <cmath>

class kolo 
{
    punkt srodek;
    double promien;

public:
    kolo();
    kolo(punkt s, double p);
    ~kolo();

    punkt getMiddle();
    double getRadius();
    void setMiddle(punkt new_middle);
    void setRadius(double new_radius);

    void translacja(wektor v);
    void obrot(punkt p, double kat);
    void symetria_srodkowa(punkt p);
    void symetria_osiowa(prosta p);

    double obwod();
    double pole();
    bool czy_nalezy_do_kola(punkt p);
    void print();

};

// weryfikuje czy kolo1 zawiera sie w kolo2
bool czy_zawiera_sie(kolo kolo1, kolo kolo2);

// weryfikuje czy koła nie maja żadnych punktow wspolnych
bool czy_sa_rozlaczne(kolo kolo1, kolo kolo2);

#endif