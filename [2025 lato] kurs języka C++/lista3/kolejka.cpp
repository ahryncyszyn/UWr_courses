
#include "kolejka.hpp"
using namespace std;

// konstruktor z zadana pojemnoscia
kolejka::kolejka(int nowa_pojemnosc) : pojemnosc(nowa_pojemnosc), ile(0)
{
    tab = new punkt[pojemnosc];
}

// konstruktor delegatowy
kolejka::kolejka() : kolejka(0) {}

// konstruktor z lista inicjalizacyjna
kolejka::kolejka(initializer_list<punkt> punkty) : pojemnosc(punkty.size())
{
    tab = new punkt[pojemnosc];
    for (punkt p : punkty)
    {
        wstaw(p);
    }
    koniec += punkty.size();
}

// operator przypisania kopiujacego
kolejka& kolejka::operator=(const kolejka &inna)
{
    if (this != &inna)
    {
        delete[] tab;
        pojemnosc = inna.pojemnosc;
        poczatek = inna.poczatek;
        koniec = inna.koniec;
        tab = new punkt[pojemnosc];
        copy(inna.tab, inna.tab + pojemnosc, tab);
    }
    return *this;
}

// konstruktor kopiujacy
kolejka::kolejka(kolejka &inna)
{
    *this = inna;
}

// operator przypisania przenoszacego
kolejka& kolejka::operator=(kolejka&& inna)
{
    tab = inna.tab;
    pojemnosc = inna.pojemnosc;
    poczatek = inna.poczatek;
    koniec = inna.koniec;
    ile = inna.ile;
    inna.tab = nullptr;
    inna.pojemnosc = 0;
    inna.poczatek = 0;
    inna.koniec = 0;
    inna.ile = 0;
    return *this;
}

// konstruktor przenoszacy
kolejka::kolejka(kolejka &&inna)
{
    *this = std::move(inna);
}

// destruktor
kolejka::~kolejka()
{
    delete[] tab;
}

void kolejka::wstaw(punkt p)
{
    if (ile == pojemnosc)
    {
        throw length_error("cała kolejka już wypełniona!");
    }

    tab[koniec] = p;
    koniec = (koniec + 1) % pojemnosc;
    ile++;
}

punkt kolejka::usun()
{
    if (ile == 0)
    {
        throw length_error("nie mozna usunac elementu z pustej kolejki");
    }

    punkt p = tab[poczatek];
    tab[poczatek] = punkt();
    poczatek = (poczatek + 1) % pojemnosc;
    ile--;
    return p;
}

punkt kolejka::zprzodu()
{
    if (poczatek == koniec)
    {
        throw length_error("kolejka jest pusta");
    }
    return tab[poczatek];
}

int kolejka::dlugosc()
{
    return ile;
}

void kolejka::print()
{
    cout << "kolejka " << pojemnosc << " elemntow: ";
    for (int i = 0; i < pojemnosc; i++)
    {
        tab[i].print();
    }
    cout << "(poczatek: " << poczatek << ", koniec: " << koniec << ")\n\n";
}