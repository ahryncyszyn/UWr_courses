#include "polynomial.hpp"
#include <iostream>
using namespace std;
using namespace calc;


int main()
{
    // testing complex class -------------------------------
    complex c1;
    cout << "Domyslny konstruktor tworzy " << c1 << endl;

    complex c2(1, 1);
    cout << "Konstruktor z liczbami tworzy " << c2 << endl;

    complex c3 = c1 + c2;
    cout << "Dodawanie: " << c1 << " + " << c2 << " = " << c3 << endl;

    complex c4 = c3 - c2;
    cout << "Odejmowanie: " << c3 << " - " << c2 << " = " << c4 << endl;

    complex c5 = c3 / c2;
    cout << "Dzielenie: " << c3 << " / " << c2 << " = " << c5 << endl;

    complex c6;
    cout << "Wycztywanie liczby: " << endl;
    cin >> c6;
    cout << "Wczytwana licza to " << c6 << endl;


    // testing polynomials --------------------------------------
    cout << "\nTESTOWANIE POLYNOMIAL" << endl;

    polynomial p1;
    cout << "Domyslny konstruktor tworzy " << p1 << endl;

    polynomial p2({complex(1, 1), complex(2, 2), complex(3, 3)});
    cout << "Konstruktor z lista inicjalizacyjna " << p2 << endl;

    try
    {
        polynomial p3({complex(0, 0)}); // sprawdzic
        cout << "Konstruktow z najwyzszym wspolczynnikiem zerowym: " << p3 << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    polynomial p4 = p2;
    cout << "Konstruktor kopiujacy: " << p4 << endl;

    p1 = p4;
    cout << "Operator przypisania: " << p1 << endl;

    polynomial p5 = p1 + p4;
    cout << "Dodawanie: " << p1 << " + " << p4 << " = " << p5 << endl;

    polynomial p(2, complex{3, 3});
    polynomial p6 = p4 - p;
    cout << "Odejmowanie: " << p4 << " - " << p << " = " << p6 << endl;

    complex c(1, 0);
    cout << "Mnozenie: " << p4 << " *  " << c << " = " << p4 * c << endl;

    cout << "Wspolczynik przy x^2: " << p4[2] << endl;

    p4[2] = complex(2, 2);
    cout << "Zamiana wspolczynnika na (2+2i): " << p4 << endl;

    try
    {
        complex zero(0, 0);
        p4.set_coefficient(2, zero);
        cout << "Zamiana wspolczynnika na (2+2i): " << p4 << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}