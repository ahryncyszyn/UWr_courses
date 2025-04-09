#include <iostream>
#include <vector>
using namespace std;

// FUNKCJA           - ma dostep do wszystkich prywatnych i skladowych klasy
// ZAPRZYJAZNIONA    - deklaracja przyjazni jest w klasie uzywajac friend
//                   - nie jest skladowa klasy
//                   - moze sie przyjaznic z kiloma klasami
//                   - jezeli jest zdefiniowana w klasie to jest inline

// KLASA             - wszystkie jej metody sa zaprzyjaznione z ta klasa
// ZAPRZYJAZNIONA    - jednostronna, nieprzechodnia, niedziedziczona

class pionek
{
    int x, y;
    friend void raport(const pionek &p);
};

void raport (const pionek &p) { cout << "(" << p.x << ", " << p.y << ")"; }

// PRZECIAZANIE      - dodanie nowej implementacji operatora    
// OPERATOROW        - mozna tylko dla typowych operatorow + new + delete

class comp
{
public:
    const double re, im;
    comp (double r = 0, double i = 0) : re(r), im(i) {}
    comp (const comp &c) : re(c.re), im(c.im) {}
    comp comp::operator- (comp b)                 // jezeli jest skladowa klasy to wystarczy 
    {                                             // obiekt do ktorego porownujemy jako argument
        return comp(re - b.re, im - b.im);  
    }
};
comp operator + (comp a, comp b)
{
    return comp(a.re + b.re, a.im + b.im);
}



int main()
{
    return 0;
}