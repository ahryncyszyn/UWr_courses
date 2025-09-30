#include <iostream>
using namespace std;

// FUNKCJE WIRTUALNE - pozwalają na przedefiniowanie danej funkcji w każdej klasie pochodnej
//                   - definiowane uzywajac virtual
//                   - nadpisywane w klasie pochodnej uzywajac override

class bazowa
{
public:
    void opis_zwykly ();
    virtual void opis_wirtualny ();
};

class pochodna: public bazowa
{
public:
    void opis_zwykly ();
    void opis_wirtualny () override;
};

void bazowa::opis_zwykly() { cout << "bazowa::opis_zwykly()" << endl; }
void bazowa::opis_wirtualny() { cout << "bazowa::opis_wirtualny()" << endl; }
void pochodna::opis_zwykly() { cout << "pochodna::opis_zwykly()" << endl; }
void pochodna::opis_wirtualny() { cout << "pochodna::opis_wirtualny()" << endl; }

// KLASA POLIMORFICZNA - klasa z funkcjami wirtualnymi
//                     - aby zachowanie obiektu bylo polimorficzne nalezy sie 
//                       do niego odnosic przez wskaznik / referencje
//                     - destruktor powinien byc wirtualny

// WYNIK FUNKCJI WIRTUALNEJ - powinien byc identyczny lub kowariantny
//                            (referencja lub wskaźnik do obiektu tej samej klasy 
//                             lub do klasy, dla której jest ona jednoznaczną i dostępną klasą bazową)
// owoc* bazowa::fun () {/*…*/}
// pomelo* pochodna::fun () {/*…*/}

// KLASA ABSTRAKCYJNA - zawiera min. 1 metode czysto wirtualna
//                    - nie mozna utworzyc jej obiektu
// virtual typ funkcja (lista-argumentów) = 0;

int main()
{
    bazowa *a = new bazowa();
    a -> opis_zwykly();
    a -> opis_wirtualny();

    bazowa *b = new pochodna();
    b -> opis_zwykly();
    b -> opis_wirtualny();
}