#pragma once

#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdint>
#include <string>
#include <map>

namespace obliczenia
{

class wymierna
{
    int licz, mian;
    void zweryfikuj_i_skroc();

public:
    wymierna();
    wymierna(int num);
    wymierna(int p, int q);
    wymierna(const wymierna& w) = default;

    int licznik() const noexcept;
    int mianownik() const noexcept;

    wymierna& operator+=(const wymierna& w);
    wymierna& operator-=(const wymierna& w);
    wymierna& operator*=(const wymierna& w);
    wymierna& operator/=(const wymierna& w);

    wymierna operator-() const noexcept;
    wymierna operator!() const;

    explicit operator int() const noexcept;
    operator double() const noexcept;

    friend wymierna operator+(wymierna lhs, const wymierna& rhs);
    friend wymierna operator-(wymierna lhs, const wymierna& rhs);
    friend wymierna operator*(wymierna lhs, const wymierna& rhs);
    friend wymierna operator/(wymierna lhs, const wymierna& rhs);
    friend std::ostream& operator<<(std::ostream& wy, const wymierna& w);
};

class wyjatek_wymierny : public std::logic_error 
{
public:
    explicit wyjatek_wymierny(const std::string& msg) : std::logic_error(msg) {}
};

class dzielenie_przez_0 : public wyjatek_wymierny 
{
public:
    dzielenie_przez_0() : wyjatek_wymierny("Dzielenie przez zero!") {}
};

class przekroczenie_zakresu : public wyjatek_wymierny 
{
public:
    przekroczenie_zakresu() : wyjatek_wymierny("Przekroczenie zakresu typu int!") {}
};

}