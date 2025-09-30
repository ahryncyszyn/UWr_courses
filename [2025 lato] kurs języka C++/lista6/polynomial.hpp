#ifndef polynomial_hpp
#define polynomial_hpp

#include "complex.hpp"
using namespace math;

namespace calc 
{
    class polynomial 
    {
        int n;
        complex *a;
        
    public:
        polynomial (int n = 1, complex wsp = complex(1, 0));
        polynomial (int n, const complex wsp[]);
        polynomial (std::initializer_list<complex> wsp);
        polynomial (const polynomial &p);
        polynomial (polynomial &&p);
        polynomial& operator = (const polynomial &p);
        polynomial& operator = (polynomial &&p);
        int get_n() const { return n; };
        ~polynomial ();

        friend polynomial operator + (const polynomial &p1, const polynomial &p2);
        friend polynomial operator - (const polynomial &p1, const polynomial &p2);
        friend polynomial operator * (const polynomial &p1, const polynomial &p2);
        friend polynomial operator * (const polynomial &p, complex c);
        friend std::ostream& operator << (std::ostream &wy, const polynomial &w);

        complex operator () (complex x) const;
        complex operator [] (int x) const;
        complex& operator [] (int x);
        void set_coefficient(int i, const complex& value);

    }; 
}

#endif