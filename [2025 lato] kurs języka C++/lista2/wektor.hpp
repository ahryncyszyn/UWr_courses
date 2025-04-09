#ifndef wektor_hpp
#define wektor_hpp

class wektor
{
    double dx, dy;

public:
    wektor();
    wektor(double new_dx, double new_dy);
    ~wektor();

    double getDx() const;
    double getDy() const;
};

#endif