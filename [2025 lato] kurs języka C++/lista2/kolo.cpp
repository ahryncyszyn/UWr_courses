#include "kolo.hpp"

const double PI = 3.14159265358979311600;

kolo::kolo() : srodek(0, 0), promien(1) {};

kolo::~kolo() {};

kolo::kolo(punkt s, double p) : srodek(s), promien(p) 
{
    if (p < 0) 
    {
        throw std::invalid_argument("Promien nie może byc mniejszy od 0");
    }
};

punkt kolo::getMiddle()
{
    return srodek;
}

double kolo::getRadius()
{
    return promien;
}

void kolo::setMiddle(punkt new_middle)
{
    srodek = new_middle;
}

void kolo::setRadius(double new_radius)
{
    if (new_radius < 0) 
    {
        throw std::invalid_argument("Promien nie może byc mniejszy od 0");
    }
    promien = new_radius;
}

void kolo::translacja(wektor v)
{
    srodek.translacja(v);
} 

void kolo::obrot(punkt p, double kat_stopnie)
{
    srodek.obrot(p, kat_stopnie);
} 

void kolo::symetria_srodkowa(punkt p)
{
    srodek.symetria_srodkowa(p);
}

void kolo::symetria_osiowa(prosta p)
{
    srodek.symetria_osiowa(p);
}

double kolo::obwod()
{
    return 2 * PI * getRadius();
}

double kolo::pole()
{
    return PI * getRadius() * getRadius();
}

bool kolo::czy_nalezy_do_kola(punkt p)
{
    double x = p.getX();
    double y = p.getY();
    double a = srodek.getX();
    double b = srodek.getY();
    return (x - a) * (x - a) + (y - b) * (y - b) <= (promien * promien);
}

bool czy_zawiera_sie(kolo kolo1, kolo kolo2)
{
    double r1 = kolo1.getRadius();
    double r2 = kolo2.getRadius();
    double distance = odleglosc(kolo1.getMiddle(), kolo2.getMiddle());
    return distance <= (r2 - r1);
}

bool czy_sa_rozlaczne(kolo kolo1, kolo kolo2)
{
    double r1 = kolo1.getRadius();
    double r2 = kolo2.getRadius();
    double distance = odleglosc(kolo1.getMiddle(), kolo2.getMiddle());
    return (distance > (r2 - r1) && (distance < std::abs(r1 - r2)));
}

void kolo::print()
{
    std::cout << "Koło: środek = (" << srodek.getX() << ", " << srodek.getY() 
              << "), promień = " << promien << "\n";
}