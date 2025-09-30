#include "complex.hpp"

namespace math 
{
    complex operator+(const complex &x, const complex &y)
    {
        return complex(x.re() + y.re(), x.im() + y.im());
    }

    complex operator-(const complex &x, const complex &y)
    {
        return complex(x.re() - y.re(), x.im() - y.im());
    }

    complex operator*(const complex &x, const complex &y)
    {
        return complex(
            x.re() * y.re() - x.im() * y.im(), 
            x.re() * y.im() + y.re() * x.im()
        );
    }

    complex operator/(const complex &x, const complex &y)
    {
        double denom = y.re() * y.re() + y.im() * y.im();
        if (denom == 0) throw std::runtime_error("dzielenie przez zero niedozwolone");
        return complex(
            (x.re() * y.re() + x.im() * y.im()) / denom,
            (x.im() * y.re() - x.re() * y.im()) / denom
        );
    }

    bool operator==(const complex &x, const complex &y)
    {
        return x.re() == y.re() && x.im() == y.im();
    }

    std::ostream& operator<<(std::ostream &os, const complex &c)
    {
        os << "(" << c.re();
        if (c.im() >= 0) os << "+";
        os << c.im() << "i)";
        return os;
    }

    std::istream& operator>>(std::istream &is, complex &c)
    {
        double r, i;
        std::cout << "Podaj realna czesc liczby\n";
        is >> r;
        std::cout << "Podaj urojona czesc liczby\n";
        is >> i;
        c.re(r);
        c.im(i);
        return is;
    }

}