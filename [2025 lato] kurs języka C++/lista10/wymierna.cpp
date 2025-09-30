#include "wymierna.hpp"

namespace obliczenia
{
    void wymierna::zweryfikuj_i_skroc()
    {
        if (mian == 0) throw dzielenie_przez_0();
        bool is_negative = false;
        if (mian < 0 || licz < 0)
        {
            is_negative = true;
            mian = abs(mian);
            licz = abs(licz);
        }
        int dzielnik = std::gcd(licz, mian);
        mian /= dzielnik;
        licz /= dzielnik;
        if (is_negative) licz = -licz;
    }

    wymierna::wymierna() : licz(0), mian(1) {};

    wymierna::wymierna(int num) : licz(num), mian(1) {};

    wymierna::wymierna(int p, int q) : licz(p), mian(q) { zweryfikuj_i_skroc(); }

    int wymierna::licznik() const noexcept { return licz; }
    int wymierna::mianownik() const noexcept { return mian; }

    wymierna& wymierna::operator+=(const wymierna& w)
    {
        long long nowy_licznik = static_cast<long long>(licz) * w.mian + static_cast<long long>(w.licz) * mian;
        long long nowy_mianownik = static_cast<long long>(mian) * w.mian;
        if (std::abs(nowy_licznik) > INT32_MAX || nowy_mianownik > INT32_MAX)
        {
            throw przekroczenie_zakresu();   
        }
        licz = static_cast<int>(nowy_licznik);
        mian = static_cast<int>(nowy_mianownik);
        zweryfikuj_i_skroc();
        return *this;
    }

    wymierna& wymierna::operator-=(const wymierna& w)
    {
        return *this += (-w);
    }

    wymierna& wymierna::operator*=(const wymierna& w)
    {
        long long nowy_licznik = static_cast<long long>(licz) * w.licz;
        long long nowy_mianownik = static_cast<long long>(mian) * w.mian;
        if (std::abs(nowy_licznik) > INT32_MAX || nowy_mianownik > INT32_MAX)
        {
            throw przekroczenie_zakresu();   
        }
        licz = static_cast<int>(nowy_licznik);
        mian = static_cast<int>(nowy_mianownik);
        zweryfikuj_i_skroc();
        return *this;
    }

    wymierna& wymierna::operator/=(const wymierna& w)
    {
        if (w.licz == 0) throw dzielenie_przez_0();
        return *this *= !w;
    }

    wymierna wymierna::operator-() const noexcept
    {
        return wymierna(-licz, mian);
    }

    wymierna wymierna::operator!() const
    {
         if (licz == 0) throw dzielenie_przez_0();
        return wymierna(mian * (licz > 0 ? 1 : -1), std::abs(licz));
    }

    wymierna::operator int() const noexcept
    {
        return static_cast<int>(std::round(static_cast<double>(*this)));
    }

    wymierna::operator double() const noexcept
    {
        return static_cast<double>(licz) / mian;
    }

    wymierna operator+(wymierna lhs, const wymierna& rhs) 
    {
        return lhs += rhs;
    }
    wymierna operator-(wymierna lhs, const wymierna& rhs) 
    {
        return lhs -= rhs;
    }
    wymierna operator*(wymierna lhs, const wymierna& rhs) 
    {
        return lhs *= rhs;
    }
    wymierna operator/(wymierna lhs, const wymierna& rhs) 
    {
        return lhs /= rhs;
    }

    std::ostream& operator<<(std::ostream& wy, const wymierna& w)
    {
        if (w.licznik() == 0) 
        {
            wy << "0";
            return wy;
        }

        bool is_negative = (w.licznik() < 0);
        int licz = std::abs(w.licznik());
        int mian = w.mianownik();

        int calosc = licz / mian;
        int reszta = licz % mian;

        if (is_negative) wy << '-';
        wy << calosc;

        if (reszta == 0)
            return wy;

        wy << ".";

        std::map<int, int> seen;
        std::string ulamek;
        int pozycja = 0;
        bool is_repeating = false;
        int repeat_start = 0;

        while (reszta != 0) 
        {
            if (seen.count(reszta)) 
            {
                is_repeating = true;
                repeat_start = seen[reszta];
                break;
            }
            seen[reszta] = pozycja++;
            reszta *= 10;
            ulamek += std::to_string(reszta / mian);
            reszta %= mian;
        }

        if (is_repeating) 
        {
            wy << ulamek.substr(0, repeat_start) << '(' << ulamek.substr(repeat_start) << ')';
        } else 
        {
            wy << ulamek;
        }

        return wy;
    }
}