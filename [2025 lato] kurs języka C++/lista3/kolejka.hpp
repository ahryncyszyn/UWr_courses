#ifndef kolejka_hpp
#define kolejka_hpp

#include "punkt.hpp"
#include <stdexcept>
using namespace std;

class kolejka
{
    int pojemnosc;
    int poczatek = 0, koniec = 0;
    int ile = 0;
    punkt *tab;

    public:
    kolejka(int nowa_pojemnosc);
    kolejka();
    kolejka(initializer_list<punkt>);
    kolejka& operator=(const kolejka &inna);
    kolejka(kolejka &inna);
    kolejka& operator=(kolejka&& inna);
    kolejka(kolejka &&inna);
    ~kolejka();

    void wstaw(punkt p);
    punkt usun();
    punkt zprzodu();
    int dlugosc();
    void print();
};

#endif