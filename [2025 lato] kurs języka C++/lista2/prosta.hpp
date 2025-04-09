#ifndef prosta_hpp
#define prosta_hpp
#include <stdexcept>

class prosta
{
    // Ax + By + C = 0
    double A, B, C;

public:
    prosta();
    prosta(double A, double B, double C);
    ~prosta();

    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double new_A);
    void setB(double new_B);
    void setC(double new_C);
};

#endif