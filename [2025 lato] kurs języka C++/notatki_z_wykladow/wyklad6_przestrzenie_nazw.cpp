
#include <iostream>
#include <string>

// PRZESTRZEN - obszar, w ktorym umieszcza sie rozne deifnicje i deklaracje
// NAZW       - definiuje zasieg dostepnosci tych nazw
//            - rozwiazuja problem kolizji nazw i wspieraja modularnosc

// namespace przestrzeń
// {
//    deklaracje i definicje
// }

// poza przestrzenia trzeba uzywac
// przestrzen::zmienna

// dla zmiennych globalnych trzeba uzywac
// ::zmienna

namespace wybory
{
    int min2 (int, int);
    int min3 (int, int, int);
}
int wybory::min2 (int a, int b) { return a<b ? a : b; }
int wybory::min3 (int a , int b , int c) { return min2(min2(a,b),c); }
int wybory::min3 (int a , int b , int c) { return min2(min2(a,b),c); }
int min4 (int a, int b, int c, int d)
{
    return wybory::min2( wybory::min2(a,b), wybory::min2(c,d));
}

namespace American_Telephone_and_Telegraph
{
    using Napis = std::string;
}
namespace ATT = American_Telephone_and_Telegraph; // alias nazw
American_Telephone_and_Telegraph::Napis n = "x";
ATT::Napis nn = "y";

// INLINE - pomaga wybrac ostateczna wersje namespace
namespace Popular {
    // przestrzeń domyślna
    inline namespace v3 {
    int f(int);
    double f(double);
    }
    namespace v2 {
    int f(int);
    int g(double);
    }
    namespace v1 {
    int f(int);
    }
    }

int main()
{
    
    return 0;
}