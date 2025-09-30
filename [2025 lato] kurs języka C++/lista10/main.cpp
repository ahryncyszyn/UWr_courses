#include "wymierna.hpp"
using namespace std;
using namespace obliczenia;

int main()
{
    // konstruktor domyslny
    wymierna a;
    cout << "Konstruktor domyslny: " << a << endl;

    // konstruktor int
    wymierna b(5);
    cout << "Konstruktor int: " << b << endl;

    // konstruktor ulamka
    wymierna c(2, 3);
    cout << "Konstruktor ulamka: " << c << endl;

    cout << "Getter licznika: " << c.licznik() << endl;
    cout << "Getter mianownika: " << c.mianownik() << endl;

    // dodawanie
    wymierna d(1, 3);
    wymierna e = c + d;
    cout << "Dodawanie: 2/3 + 1/3 = " << e << endl;

    e += wymierna(1, 4);
    cout << "Dodawanie: 1 + 1/4 = " << e << endl;

    // odejmowanie 
    e -= wymierna(1, 4);
    cout << "Odejmowanie: 1.25 - 0.25 = " << e << endl;

    // mnozenie 
    e *= wymierna(1, 2);
    cout << "Mnozenie: 1.0 * 1/2 = " << e << endl;

    wymierna h(2359348, 99900);
    cout << "TESTTTT " << h << endl;

    // test przekraczania zakresu int
    try
    {
        wymierna f(INT_MAX, 1);
        f *= f;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // dzielenie
    e /= wymierna(2, 1);
    cout << "Mnozenie: 1/2 / 2 = " << e << endl;

    // test dzielenie przez 0
    try
    {
        e /= 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // test skracania ułamka
    wymierna g(25, 5);
    cout << "Ułamek 25/5 skrocony do: " << g << endl;
}