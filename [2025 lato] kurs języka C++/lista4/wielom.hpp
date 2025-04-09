#ifndef wielom_hpp
#define wielom_hpp

#include <stdexcept>
#include <iostream>
using namespace std;

class wielom 
{
    int n; // stopień wielomianu
    double *a; // współczynniki wielomianu;

    public:
    wielom (int st = 0, double wsp = 1.0); // konstruktor jednomianu
    wielom (int st, const double wsp[]); // konstruktor wielomianu
    wielom (initializer_list<double> wsp); // lista współczynników
    wielom (const wielom &w); // konstruktor kopiujący
    wielom (wielom &&w); // konstruktor przenoszący
    wielom& operator = (const wielom &w); // przypisanie kopiujące
    wielom& operator = (wielom &&w); // przypisanie przenoszące
    ~wielom (); // destruktor

    friend istream& operator >> (istream &we, wielom &w); 
    friend ostream& operator << (ostream &wy, const wielom &w); 

    friend wielom operator + (const wielom &u, const wielom &v); 
    friend wielom operator - (const wielom &u, const wielom &v); 
    friend wielom operator * (const wielom &u, const wielom &v); 
    friend wielom operator * (const wielom &u, double c); 
    wielom& operator += (const wielom &v); 
    wielom& operator -= (const wielom &v); 
    wielom& operator *= (const wielom &v); 
    wielom& operator *= (double c); 
    double operator () (double x) const; // wartość wielomianu dla x 
    double operator [] (int i) const; // do odczytu współczynnika 
    double& operator [] (int i); // do zapisu współczynnika
   };


#endif