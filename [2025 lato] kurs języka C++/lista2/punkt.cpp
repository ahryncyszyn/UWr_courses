#include "punkt.hpp"

const double PI = 3.14159265358979311600;

punkt::punkt() : x(0), y(0) {};

punkt::punkt(double new_x, double new_y) : x(new_x), y(new_y) {};

punkt::~punkt() {};

double punkt::getX() const
{
    return x;
}

double punkt::getY() const
{
    return y;
}

void punkt::setX(double new_x)
{
    x = new_x;
}

void punkt::setY(double new_y)
{
    y = new_y;
}

void punkt::translacja(wektor v)
{
    setX(x + v.getDx());
    setY(y + v.getDy());
}

void punkt::obrot(punkt p, double kat_stopnie)
{
    double x0 = p.getX();
    double y0 = p.getY();

    double radiany = kat_stopnie * PI / 180;
    double cos_theta = std::cos(radiany);
    double sin_theta = std::sin(radiany);

    setX(x0 + (x - x0) * cos_theta - (y - y0) * sin_theta);
    setY(y0 + (x - x0) * sin_theta + (y - y0) * cos_theta);
}

void punkt::symetria_srodkowa(punkt p)
{
    setX(2 * p.getX() - x);
    setY(2 * p.getY() - y);
}

void punkt::symetria_osiowa(prosta p)
{
    double A = p.getA();
    double B = p.getB();
    double C = p.getC();
    double dist = (A * x + B * y + C) / (A * A + B * B); 
    setX(x - 2 * dist * A);
    setY( y - 2 * dist * B);
}

double odleglosc(const punkt& p1, const punkt& p2) {
    double dx = p1.getX() - p2.getX();
    double dy = p1.getY() - p2.getY();
    return sqrt(dx * dx + dy * dy);
}

void punkt::print() 
{
    std::cout << "Punkt: (" << x << ", " << y << ")\n";
}