#include "wyrazenie.hpp"
#include "zmienne.hpp"
#include "operatory.hpp"
#include <iostream>
using namespace obliczenia;

std::vector<std::pair<std::string, int>> zmienna::zmienne;

int main() 
{
    zmienna::add_variable("x", 12);
    wyrazenie* w1 = new potega(
        new liczba(2),
        new odejmowanie(
            new dzielenie(
                new zmienna("x"),
                new liczba(3)
            ),
            new liczba(1)
        )
    );

    zmienna::add_variable("y", 10);
    wyrazenie* w2 = new mnozenie(
        new dodawanie(
            new zmienna("x"),
            new zmienna("y")
        ),
        new odejmowanie(
            new zmienna("x"),
            new zmienna("y")
        )
    );

    wyrazenie* w3 = new obliczenia::minus(
        new dzielenie(
            new dodawanie(
                new zmienna("x"),
                new liczba(2)
            ),
            new zmienna("y")
        )
    );

    wyrazenie* w4 = new dodawanie(
        new mnozenie(
            new liczba(2),
            new zmienna("x")
        ),
        new mnozenie(
            new liczba(3),
            new zmienna("y")
        )
    );

    wyrazenie* w5 = new mnozenie(
        new jeden, 
        new zero
    );

    wyrazenie* wyrazenia[] = {w1, w2, w3, w4, w5};
    for (int i = 0; i < 5; i++) 
    {
        std::cout << "Wyrażenie: " << wyrazenia[i] -> zapis() << std::endl;
        std::cout << "Wynik: " << wyrazenia[i] -> oblicz() << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    // powinno zwrocic blad - niezdefiniowana zmienna z
    try
    {
        wyrazenie* w5 = new mnozenie(
            new zmienna("z"), 
            new jeden
        );
        std::cout << "Wyrażenie: " << w5 -> zapis() << std::endl;
        std::cout << "Wynik: " << w5 -> oblicz() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // powinno zwrocic blad bo usuwamy zmienna x
    try
    {
        zmienna::remove_variable("x");
        wyrazenie* w6 = new dodawanie
        (
            new zmienna("x"), 
            new zero
        );
        std::cout << "Wyrażenie: " << w6 -> zapis() << std::endl;
        std::cout << "Wynik: " << w6 -> oblicz() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // powinno zwrocic blad dzielenia przez 0
    zmienna::add_variable("x", 0);
    try
    {
        wyrazenie* w7 = new dzielenie
        (
            new jeden, 
            new zmienna("x")
        );
        std::cout << "Wyrażenie: " << w7 -> zapis() << std::endl;
        std::cout << "Wynik: " << w7 -> oblicz() << std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    delete w1;
    delete w2;
    delete w3;
    return 0;
}