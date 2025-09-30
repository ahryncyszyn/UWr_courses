#include <iostream>
#ifndef complex_HPP
#define complex_HPP

namespace math
{
    class  complex 
    { 
        double r, i; 

    public: 
        complex(double a = 0, double b = 0) : r(a), i(b) { } 
    
        double re() const { return r; };
        double im() const { return i; };
        void re(double new_r) { r = new_r; };
        void im(double new_i) { i = new_i; };
        complex conjugated() const { return complex(r, -i); };
    }; 
    
    complex operator+(const complex &x, const complex &y); 
    complex operator-(const complex &x, const complex &y); 
    complex operator*(const complex &x, const complex &y); 
    complex operator/(const complex &x, const complex &y); 
    bool operator==(const complex &x, const complex &y);
    
    std::ostream& operator<<(std::ostream &os, const complex &c); 
    std::istream& operator>>(std::istream &is, complex &c); 
}

#endif