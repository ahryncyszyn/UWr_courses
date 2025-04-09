
#include <iostream>
#include "punkt.hpp"
#include "kolo.hpp"
using namespace std;

int main()
{
    // PUNKT ----------------------------------------------
    punkt p1;
    cout << "Domyślny punkt: ";
    p1.print();

    punkt p2(3, 4);
    cout << "Punkt z parametrami: ";
    p2.print();

    p2.setX(2);
    p2.setY(2);
    cout << "Zaktualizowany punkt: ";
    p2.print();

    p2.translacja(wektor(-1, -1));
    cout << "Punkt po translacji: ";
    p2.print();

    p2.obrot(punkt(0, 0), -90);
    cout << "Punkt po obrocie: ";
    p2.print();

    p2.symetria_srodkowa(punkt(0, 0));
    cout << "Punkt po symetrii środkowej: ";
    p2.print();

    p2.symetria_osiowa(prosta(1, -1, 0));
    cout << "Punkt po symetrii osiowej: ";
    p2.print();

    cout << "Odleglosc miedzy p1 i p2 to: " << odleglosc(p1, p2) << endl;
    cout << "\n";

    // KOLO ----------------------------------------------
    kolo kolo1;
    cout << "Domyślny konstruktor kolo: ";
    kolo1.print();

    punkt srodek(2, 3);
    kolo kolo2(srodek, 5);
    cout << "Kolo z parametrami: ";
    kolo2.print();

    try 
    {
        punkt p(0, 0);
        kolo bledne_kolo(p, -5.0);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Błąd: " << e.what() << "\n";
    }

    punkt nowy_srodek(1, 1);
    kolo2.setMiddle(nowy_srodek);
    kolo2.setRadius(5);
    cout << "Zaktualizowane kolo2: ";
    kolo2.print();

    kolo2.translacja(wektor(1, 1));
    cout << "Kolo po translacji: ";
    kolo2.print();

    kolo2.obrot(punkt(0, 0), 90);
    cout << "Kolo po obrocie: ";
    kolo2.print();

    p2.symetria_srodkowa(punkt(0, 0));
    cout << "Kolo po symetrii środkowej: ";
    kolo2.print();

    p2.symetria_osiowa(prosta(1, -1, 0));
    cout << "Kolo po symetrii osiowej: ";
    kolo2.print();

    cout << "Obwód kolo2: " << kolo2.obwod() << "\n";
    cout << "Pole kolo2: " << kolo2.pole() << "\n";

    cout << "Czy p1 należy do kolo2? " << (kolo2.czy_nalezy_do_kola(p1) ? "Tak" : "Nie") << "\n";
    cout << "Czy p2 należy do kolo2? " << (kolo2.czy_nalezy_do_kola(p2) ? "Tak" : "Nie") << "\n";

    cout << "Czy kolo1 zawiera sie w kolo2? " << (czy_zawiera_sie(kolo1, kolo2) ? "Tak" : "Nie") << "\n";
    cout << "Czy kolo1 i kolo2 są rozłączne? " << (czy_sa_rozlaczne(kolo1, kolo2) ? "Tak" : "Nie") << "\n";
    return 0;
}