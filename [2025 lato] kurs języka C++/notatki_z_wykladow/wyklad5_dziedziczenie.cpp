#include <iostream>
#include <vector>
using namespace std;

// DZIEDZICZENIE - pozwala tworzyc nowa klase wykorzystujac juz istniejaca
// KLASA POCHODNA - moze miec nowe pola skladowe, funkcje skladowe
//                - moze miec nadpisane funkcje skladowe
//                - wszystko jest dziedziczone, ale elementy o tej samej nazwie zaslaniaja
//                      - poza konstruktorem, destruktorem, operatorami przypisania

// dziedziczenie skadnikow:
// PRIVATE - brak dostepu
// PROTECTED - dostepne, ale nie na zewnatrz
// PUBLIC - dostepne, tez na zewntarz

// rodzaje dziedziczenia
// PRIVATE - dziedziczone skladniki nieprywatne staja sie prywatne, domyslna opcja
// PROTECTED - dziedziczone skladniki nieprywatne staja sie chronione
// PUBLIC - dziedziczone skladniki nieprywatne zostaja nieprywatne

// klasa bazowa, nadklasa
class punkt2D
{
protected:
    double x, y;
public:
    punkt2D() : x(0), y(0) {};
    string opis() const;
};

// klasa pochodna, podklasa
class punkt3D : public punkt2D
{
protected:
    double z;
public:
    punkt3D() : punkt2D(), z(0) {};
    double odleglosc (const punkt3D &p) const;
    string opis() const;
};

// USING - pozwala na wybiorcze przywrocenie pierwotnego
//         zakresu widocznosci przy dziedziczeniu niepublicznym

// FINAL - klasa z ktorej nie mozna dziedziczyc
class P final : public B {};

// DEFAULT - generuje domyslny konstruktor
struct SomeType 
{
    SomeType () = default;
    SomeType (OtherType value);
};

// DELETE - blokuje mechanizm generowania domyslnych metod
struct NonCopyable 
{
    // konstruktor kopiujący i przypisanie kopiujące
    // nie zostaną wygenerowane
    NonCopyable& operator= (const NonCopyable&) = delete;
    NonCopyable (const NonCopyable&) = delete;
    NonCopyable () = default;
};

struct NonNewable 
{
    // obiektów nie można utworzyć za pomocą operatora new
    void* operator new (std::size_t) = delete;
};

struct NoDouble 
{
    void f (double d);
    // zakazuje wywolania f() z arguementem int
    // gdyby nie delete to int zostalby zcastowany na double
    void f (int) = delete;
};

/*
class potomek: private przodek
{
protected:
    using przodek::polechro;
    using przodek::funchro;
public:

    using przodek::polepub;
    using przodek::funpub;
};
*/

// DZIEDZICZENIE WIRTUALNE - zapewnia ze tylko jedna wersja klasy basowej jest odziedziczona
class Animal 
{
    virtual ~Animal() = default;
    virtual void Eat() {}
};

class Mammal: virtual Animal 
{
    virtual void Breathe() {}
};

class WingedAnimal: virtual Animal 
{
    virtual void Flap() {}
};

class Bat: Mammal, WingedAnimal {};

// POD - plain old data, struktury danych zgodne z ANSI C
//     - typy podstawowe w c++ sie zaliczaja
//     - klasy tez jezeli maja tylko konstruktor domyslny / destruktor nic nie robi,
//       ten sam poziom dostepu dla wszystkich niestatycznych skladowych,
//       brak wirtualnych metod, ani klas
//       tylko jedna klasa z niestatycznymi skladowymi w calej hierarchii
//       inicjalizowane przez liste argumentow o kolejnosc zgodnej ze skladowymi

int main()
{
    // mozna sie odnosic do nadpisanych funkcji uzywajac base_class::
    punkt3D p();
    cout << p.punkt2D::opis() << endl;
}