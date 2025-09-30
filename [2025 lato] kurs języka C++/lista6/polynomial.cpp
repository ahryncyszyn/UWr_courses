
#include "polynomial.hpp"
#include <cstring>

namespace calc
{
    polynomial::polynomial (int n, complex wsp) : n(n)
    {
        if (n < 0)
        {
            throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
        }
        a = new complex[n + 1];
        for (int i = 0; i <= n; i++)
        {
            if (i == n) a[i] = wsp;
            else a[i] = complex(0, 0);
        }
    }

    polynomial::polynomial (int n, const complex wsp[]) : n(n)
    {
        if (n < 0)
        {
            throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
        }
        if (wsp[n] == 0)
        {
            throw std::invalid_argument("Współczynnik przy najwyzszej potedze nie moze byc zerowy");
        }
        a = new complex[n + 1];
        for (int i = 0; i <= n; i++)
        {
            a[i] = wsp[i];
        }
    }

    polynomial::polynomial (std::initializer_list<complex> wsp) : n(wsp.size() - 1)
    {
        if (*std::prev(wsp.end()) == complex(0, 0))
        {
            throw std::invalid_argument("Współczynnik przy najwyższej potędze nie może być zerowy");
        }
        a = new complex[n + 1];
        int i = 0;
        for (complex c : wsp)
        { 
            a[i++] = c;
        }
    }

    polynomial::polynomial (const polynomial &p) : n(p.n)
    {
        a = new complex[n + 1];
        std::memcpy(a, p.a, (n + 1) * sizeof(complex));
    }

    polynomial::polynomial (polynomial &&p) : n(p.n), a(p.a)
    {
        p.a = nullptr;
    }

    polynomial& polynomial::operator = (const polynomial &p)
    {
        delete[] a;
        n = p.n;
        a = new complex[n + 1];
        std::memcpy(a, p.a, (n + 1) * sizeof(complex));
        return *this;
    }

    polynomial& polynomial::operator = (polynomial &&p)
    {
        if (this == &p)
        {
            return *this;
        }
        delete[] a;
        n = p.n;
        a = p.a;
        p.a = nullptr;
        return *this;
    }

    polynomial::~polynomial() { delete[] a; }

    polynomial operator + (const polynomial &p1, const polynomial &p2)
    {
        int max_n = std::max(p1.n, p2.n);
        while (p1.n == max_n && p2.n == max_n
                && p1.a[max_n] + p2.a[max_n] == 0)
        {
            max_n--;
        }

        polynomial p(max_n, complex(0, 0));
        for (int i = 0; i <= max_n; i++)
        {
            if (i <= p1.n) p.a[i] = p.a[i] + p1.a[i];
            if (i <= p2.n) p.a[i] = p.a[i] + p2.a[i];
        }
        return p;
    }

    polynomial operator - (const polynomial &p1, const polynomial &p2)
    {
        int max_n = std::max(p1.n, p2.n);
        while (p1.n == max_n && p2.n == max_n
                && p1.a[max_n] - p2.a[max_n] == 0)
        {
            max_n--;
        }

        polynomial p(max_n, complex(0, 0));
        for (int i = 0; i <= max_n; i++)
        {
            if (i <= p1.n) p.a[i] = p.a[i] + p1.a[i];
            if (i <= p2.n) p.a[i] = p.a[i] - p2.a[i];
        }
        return p;
    }

    polynomial operator * (const polynomial &p1, const polynomial &p2)
    {
        int new_n = p1.n + p2.n;
        complex* a = new complex[new_n + 1];

        for (int i = 0; i <= p1.n; i++)
        {
            for (int j = 0; j <= p2.n; j++)
            {
                a[i + j] = a[i + j] + (p1.a[i] * p2.a[j]);
            }
        }
        return polynomial(new_n, a);
    }

    polynomial operator * (const polynomial &p, complex c)
    {
        for (int i = 0; i < p.n; i++)
        {
            p.a[i] = p.a[i] * c;
        }
        return p;
    }

    complex polynomial::operator () (complex x) const
    {
        complex res(0, 0);
        for (int i = n - 1; i >= 0; i--)
        {
            res = res * x + a[i];
        }
        return res;
    }

    complex polynomial::operator [] (int i) const 
    {
        if (i < 0 || i > n) 
        {
            throw std::out_of_range("indeks poza zakresem");
        }
        return a[i];
    }

    // nie da sie bezpiecznie nadpisywac wspolczynnikow uzywajac tego przeciazenia
    // bo ten kod sprawdza tylko obecna wartosc wspolczynnika, nie ma dostepu do nowej
    complex& polynomial::operator [] (int i)
    {
        if (i < 0 || i > n) 
        {
            throw std::out_of_range("indeks poza zakresem");
        }
        return a[i];
    }

    // ta wersja ustawiania nowego wspolczynnika jest bezpieczniejsza
    void polynomial::set_coefficient(int i, const complex& value)
    {
        if (i < 0 || i > n)
        {
            throw std::out_of_range("indeks poza zakresem");
        }
        if (i == n && value == complex(0, 0))
        {
            throw std::invalid_argument("nie można ustawić współczynnika przy najwyższej potędze na 0");
        }
        a[i] = value;
    }

    std::ostream& operator << (std::ostream &wy, const polynomial &w)
    {
        for (int i = w.n; i >= 0; i--) 
        {
            wy << w.a[i];
            if (i != 0) wy << "x";
            if (i != 0 && i != 1) wy << "^" << i;
            if (i != 0) wy << " + ";
        }
        return wy;
    }
}