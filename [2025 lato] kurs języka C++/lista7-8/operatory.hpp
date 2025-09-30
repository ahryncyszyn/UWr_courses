#pragma once
#include "wyrazenie.hpp"
#include <iostream>
using namespace std;

namespace obliczenia {

class operator1 : public wyrazenie
{
protected:
    wyrazenie* arg1;
public:
    operator1(wyrazenie* a) : arg1(a) {};
    ~operator1() override { delete arg1; };
};

class minus : public operator1
{
public:
    minus(wyrazenie* a) : operator1(a) {};
    int oblicz() override { return -(arg1 -> oblicz()); };
    string zapis() override { return "-(" + arg1 -> zapis() + ")"; };
};

class operator2 : public operator1 
{
protected:
    wyrazenie* arg2;
public:
    operator2(wyrazenie* a, wyrazenie* b) : operator1(a), arg2(b) {};
    ~operator2() { delete arg2; };
};

class dodawanie : public operator2 
{
public:
    dodawanie(wyrazenie* a, wyrazenie* b) : operator2(a, b) {}
    int oblicz() override { return arg1 -> oblicz() + arg2 -> oblicz(); }
    std::string zapis() override 
    {
        std::string l = arg1 -> zapis(), r = arg2 -> zapis();
        if (dynamic_cast<liczba*>(arg1) == nullptr && dynamic_cast<zmienna*>(arg1) == nullptr &&
            arg1 -> priorytet() < priorytet()) l = "(" + l + ")";
        if (dynamic_cast<liczba*>(arg2) == nullptr && dynamic_cast<zmienna*>(arg2) == nullptr &&
            arg2 -> priorytet() < priorytet()) r = "(" + r + ")";
        return l + " + " + r;
    }
    int priorytet() override { return 2; };
};

class odejmowanie : public operator2 
{
public:
    odejmowanie(wyrazenie* a, wyrazenie* b) : operator2(a, b) {}
    int oblicz() override { return arg1 -> oblicz() - arg2 -> oblicz(); }
    std::string zapis() override 
    {
        std::string l = arg1 -> zapis(), r = arg2 -> zapis();
        if (dynamic_cast<liczba*>(arg1) == nullptr && dynamic_cast<zmienna*>(arg1) == nullptr &&
            arg1 -> priorytet() < priorytet()) l = "(" + l + ")";
        if (dynamic_cast<liczba*>(arg2) == nullptr && dynamic_cast<zmienna*>(arg2) == nullptr &&
            arg2 -> priorytet() < priorytet()) r = "(" + r + ")";
        return l + " - " + r;
    }
    int priorytet() override { return 2; };
};

class mnozenie : public operator2 
{
public:
    mnozenie(wyrazenie* a, wyrazenie* b) : operator2(a, b) {}
    int oblicz() override { return arg1 -> oblicz() * arg2 -> oblicz(); }
    std::string zapis() override 
    {
        std::string l = arg1 -> zapis(), r = arg2 -> zapis();
        if (dynamic_cast<liczba*>(arg1) == nullptr && dynamic_cast<zmienna*>(arg1) == nullptr &&
            arg1 -> priorytet() < priorytet()) l = "(" + l + ")";
        if (dynamic_cast<liczba*>(arg2) == nullptr && dynamic_cast<zmienna*>(arg2) == nullptr &&
            arg2 -> priorytet() < priorytet()) r = "(" + r + ")";
        return l + " * " + r;
    }
    int priorytet() override { return 3; };
};

class dzielenie : public operator2 
{
public:
    dzielenie(wyrazenie* a, wyrazenie* b) : operator2(a, b) {}
    int oblicz() override 
    {
        int d = arg2 -> oblicz();
        if (d == 0) throw std::runtime_error("dzielenie przez zero niedozwolone");
        return arg1 -> oblicz() / d;
    }
    std::string zapis() override 
    {
        std::string l = arg1 -> zapis(), r = arg2 -> zapis();
        if (dynamic_cast<liczba*>(arg1) == nullptr && dynamic_cast<zmienna*>(arg1) == nullptr &&
            arg1 -> priorytet() < priorytet()) l = "(" + l + ")";
        if (dynamic_cast<liczba*>(arg2) == nullptr && dynamic_cast<zmienna*>(arg2) == nullptr &&
            arg2 -> priorytet() < priorytet()) r = "(" + r + ")";
        return l + " / " + r;
    }
    int priorytet() override { return 3; };
};

class potega : public operator2 
{
public:
    potega(wyrazenie* a, wyrazenie* b) : operator2(a, b) {}
    int oblicz() override { return std::pow(arg1 -> oblicz(), arg2 -> oblicz()); }
    std::string zapis() override 
    {
        std::string l = arg1 -> zapis(), r = arg2 -> zapis();
        if (dynamic_cast<liczba*>(arg1) == nullptr && dynamic_cast<zmienna*>(arg1) == nullptr &&
            arg1 -> priorytet() < priorytet()) l = "(" + l + ")";
        if (dynamic_cast<liczba*>(arg2) == nullptr && dynamic_cast<zmienna*>(arg2) == nullptr &&
            arg2 -> priorytet() < priorytet()) r = "(" + r + ")";
        return l + "^" + r;
    }
    int priorytet() override { return 4; };
    bool czy_lewostronna = 0;
};

}