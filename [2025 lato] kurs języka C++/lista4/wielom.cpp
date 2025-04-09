#include "wielom.hpp"
using namespace std;

// KONSTRUKTORY -------------------------------------------------------------
wielom::wielom (int st, double wsp) : n(st)
{
    a = new double[st + 1];
    for (int i = 0; i <= st; i++)
    {
        if (i == st) a[i] = wsp;
        else a[i] = 0.0;
    }
}

wielom::wielom (int st, const double wsp[]) : n(st)
{
    if (st < 0)
    {
        throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
    }
    if (st > 0 && wsp[st] == 0)
    {
        throw std::invalid_argument("Współczynnik przy najwyzszej potedze nie moze byc zerowy");
    }
    a = new double[st + 1];
    for (int i = 0; i <= n; i++)
    {
        a[i] = wsp[i];
    }
}

wielom::wielom (initializer_list<double> wsp) : n(wsp.size() - 1)
{
    if (n == 0)
    {
        throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
    }
    if (n > 1 && *std::prev(wsp.end()) == 0) 
    {
        throw std::invalid_argument("Współczynnik przy najwyższej potędze nie może być zerowy");
    }
    a = new double[n];
    int i = 0;
    for (int value : wsp) 
    {
        a[i++] = value;
    }
}

wielom::wielom (const wielom &w) : n(w.n) // konstruktor kopiujacy
{
    a = new double[n + 1];
    std::memcpy(a, w.a, (n + 1) * sizeof(double));
}

wielom::wielom (wielom &&w) : n(w.n), a(w.a) // konstruktor przenoszący
{
    w.a = nullptr;
}

wielom& wielom::operator = (const wielom &w) // przypisanie kopiujące
{
    if (this == &w)
    {
        return *this;
    }

    delete[] a;
    n = w.n;
    a = new double[n + 1];
    std::memcpy(a, w.a, (n + 1) * sizeof(double));
    return *this;
}

wielom& wielom::operator = (wielom &&w) // przypisanie przenoszące
{
    if (this == &w)
    {
        return *this;
    }

    delete[] a;
    n = w.n;
    a = w.a;
    w.a = nullptr;
    return *this;
}

wielom::~wielom () { delete[] a; }

// OPERATORY -----------------------------------------------------------------
istream& operator >> (istream &we, wielom &w)
{
    cout << "podaj stopień wielomianu: ";
    we >> w.n;

    if (w.n < 0) 
    {
        throw invalid_argument("Stopień wielomianu nie może być ujemny");
    }

    delete[] w.a;
    w.a = new double[w.n + 1];

    cout << "Podaj współczynniki od wyrazu wolnego do najwyższej potęgi:";
    for (int i = 0; i <= w.n; ++i) 
    {
        cout << "a[" << i << "]: ";
        we >> w.a[i];
    }

    if (w.a[w.n] == 0 && w.n != 0) 
    {
        throw invalid_argument("Współczynnik przy najwyższej potędze nie może być zerowy");
    }

    return we;
}

ostream& operator << (ostream &wy, const wielom &w)
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

wielom operator + (const wielom &u, const wielom &v)
{
    int max_n = std::max(u.n, v.n);
    while (u.n == max_n && u.n == max_n 
           && u.a[max_n] + v.a[max_n] == 0)
    {
        max_n--;
    }
    wielom w(max_n, 0.0);
    for (int i = 0; i <= max_n; i++)
    {
        if (i <= u.n) w.a[i] += u.a[i];
        if (i <= v.n) w.a[i] += v.a[i];
    }

    return w;
}

wielom operator - (const wielom &u, const wielom &v)
{
    int new_n = std::max(u.n, v.n);
    while (u.n == new_n && u.n == new_n 
        && u.a[new_n] - v.a[new_n] == 0)
    {
         new_n--;
    }
    wielom w(new_n, 0.0);
    for (int i = 0; i <= new_n; i++)
    {
        if (i <= u.n) w.a[i] += u.a[i];
        if (i <= v.n) w.a[i] -= v.a[i];
    }

    return w;
}

wielom operator * (const wielom &u, const wielom &v)
{
    int new_n = u.n + v.n;
    double* wsp = new double[new_n + 1]{0};

    for (int i = 0; i <= u.n; i++) 
    {
        for (int j = 0; j <= v.n; j++) 
        {
            wsp[i + j] += u.a[i] * v.a[j];
        }
    }
    return wielom(new_n, wsp);
}

wielom operator * (const wielom &u, double c)
{
    for (int i = 0; i <= u.n; i++) u.a[i] *= c;
    return u;
}

wielom& wielom::operator += (const wielom &v)
{
    *this = *this + v;
    return *this;
}

wielom& wielom::operator -= (const wielom &v)
{
    *this = *this - v;
    return *this;
}

wielom& wielom::operator *= (const wielom &v)
{
    *this = *this * v;
    return *this;
}

wielom& wielom::operator *= (double c)
{
    *this = *this * c;
    return *this;
}

double wielom::operator () (double x) const // wartość wielomianu dla x
{
    double wynik = a[n];
    for (int i = n - 1; i >= 0; i--) 
    {
        wynik = wynik * x + a[i];
    }
    return wynik;
} 

double wielom::operator [] (int i) const // do odczytu współczynnika 
{
    if (i < 0 || i > n) 
    {
        throw std::out_of_range("Indeks poza zakresem");
    }
    return a[i];
}

double& wielom::operator [] (int i) // do zapisu współczynnika
{
    if (i < 0 || i > n) 
    {
        throw std::out_of_range("Indeks poza zakresem");
    }
    if (i == n && a[i] == 0) 
    {
        throw std::invalid_argument("Nie można ustawić współczynnika przy najwyższej potędze na 0");
    }
    return a[i];
}
