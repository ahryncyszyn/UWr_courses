#pragma once
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

namespace obliczenia {

class wyrazenie
{
public:
    wyrazenie() {};
    virtual int oblicz() = 0;
    virtual string zapis() = 0;
    virtual int priorytet() { return 0; };
    static const int czy_lewostronny = 1;
    virtual ~wyrazenie() {};
};

class liczba : public wyrazenie
{
    int wartosc;
public:
    liczba(int w) : wartosc(w) {};
    int oblicz() override { return wartosc; };
    string zapis() override { return to_string(wartosc); };
    int priorytet() override { return 100; };
    ~liczba() {};
};

class stala : public wyrazenie
{
protected:
    string nazwa;
    int wartosc;
public:
    stala(string n, int w) : nazwa(n), wartosc(w) {};
    int oblicz() override { return wartosc; };
    string zapis() override { return nazwa; };
    int priorytet() override { return 100; };
    ~stala() {};
};

class zero : public stala
{
public:
    zero() : stala("0", 0) {};
};

class jeden : public stala
{
public:
    jeden() : stala("1", 1) {};
};

}