#include "kolornazwany.hpp"
#include "kolortansparentny.hpp"
#include "kolortransnaz.hpp"
#include "pikselkolorowy.hpp"

int main()
{
    cout << "KLASA KOLOR" << endl;
    kolor k1;
    cout << "Domyślny konstruktor: k1 - " << k1;

    kolor k2(25, 50, 75);
    cout << "Konstruktor z wartosciami liczbowymi: k2 - " << k2;

    try
    {
        kolor k3(500, 1, 1);
        cout << "Konstruktor z wartosciami poza zakresem" << k3;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    k2.make_darker();
    cout << "Przyciemnienie: k2 - " << k2;

    k2.make_lighter();
    k2.make_lighter();
    cout << "Rozjasnienie: k2 - " << k2;

    kolor k3(100, 100, 100);
    cout << "Polaczenie kolorow " << k2 << " i " << k3 << " to " << kolor::polacz(k2, k3);

    cout << "\nKLASA KOLOR TRANSPARENTNY" << endl;
    kolortransparentny kt1;
    cout << "Domyślny konstruktor: kt1 - " << kt1;

    kolortransparentny kt2(1, 2, 3, 4);
    cout << "Konstruktor z wartosciami liczbowymi: kt2 - " << kt2;

    try
    {
        kolortransparentny kt3(500, 1, 1, 1);
        cout << "Konstruktor z wartosciami poza zakresem" << kt3;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    kt2.set_alfa(50);
    cout << "Ustawienie nowej wartosci alfa: " << kt2;

    try
    {
        cout << "Ustawienie blednej wartosci alfa:";
        kt2.set_alfa(500);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    cout << "\nKLASA KOLOR NAZWANY" << endl;
    kolornazwany kn1;
    cout << "Domyślny konstruktor: kn1 - " << kn1;

    kolornazwany kn2(25, 50, 75, "kolor");
    cout << "Konstruktor z wartosciami liczbowymi i nazwa: kn2 - " << kn2;

    kn2.set_name("nowanazwa");
    cout << "Zmiana nazwy koloru: " << kn2;

    try
    {
        kn2.set_name("Nazwa");
        cout << "Zamiana na bledna nazwe: " << kn2;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    cout << "\nKLASA PIKSEL" << endl;
    piksel p1;
    cout << "Domyślny konstruktor: p1 - " << p1;

    piksel p2(100, 100);
    cout << "Konstruktor z wartosciami liczbowymi: p2 - " << p2;

    cout << "Odleglosc do lewej strony ekranu: " << p2.dist_from_left_side() << endl;
    cout << "Odleglosc do prawej strony ekranu: " << p2.dist_from_right_side() << endl;
    cout << "Odleglosc do gory ekranu: " << p2.dist_from_top_side() << endl;
    cout << "Odleglosc do dolu ekranu: " << p2.dist_from_bottom_side() << endl;

    cout <<  "Odleglosc miedzy pikselami " << p1 << " oraz " << p2 << " to: " << piksel::distance(p1, p2);

    cout << "\n\nKLASA PIKSEL KOLOROWY" << endl;
    pikselkolorowy pk1;
    cout << "Domyślny konstruktor: p1 - " << pk1;

    pikselkolorowy pk2(100, 100, 255, 255, 255);
    cout << "Konstruktor z wartosciami liczbowymi: p2 - " << pk2;

    pk2.move(100, 100);
    cout << "Przeniesienie piksela p2 o wektor (100, 100): " << pk2;

    try
    {
        cout << "Przeniesienie piksela poza ekran: ";
        pk2.move(10000, 10000);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
 
    return 0;
}