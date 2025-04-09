#include <iostream>
#include <bitset>
#include <string>
#include <utility>
#include <stdexcept>

// dwa rodzaje plikow: naglowkowy (.hpp) i źrodłowy (.cpp)
// włączanie warunkowe w pliku nagłowkowym: 
// #ifndef my_hpp
// #define my_hpp
// #endif
// zapobiega wielokrotnemu dołączaniu tego samego pliku podczas kompilacji

void wejscie_wyjscie()
{
    std::cout << "podaj liczbe:" << std::endl;
    int num;
    std::cin >> num;
    std::clog << "standardowe wyjscie dla bledow" << std::endl;
    std::cerr << "niebuforowane wyjscie dla bledow" << std::endl;
}

// auto - pozwala na automatyczny wybor typu zmiennej
// - musi byc od razu zainicjowana
auto x = 1.25 * 2 - 1e-6;

// decltype - pozwala na zadeklarowanie typu na podstawie wyrazenia
decltype(x / 2 + 1e-6) y = 5;

// const - deklarator do stałych
// - musi byc od raz zainicjalizowana
// - jej wartosc nie moze byc juz modyfikowana
// - lepsza od makr, bo jest znany typ i zasieg
const double phi = 1.618033989;

// constexpr - deklarator dla stalych wyrazen
// - wyliczane przez kompilator na etapie kompilacji a nie wykonania programu
constexpr double grawitacja_ziemia = 9.8;
constexpr double grawitacja_ksiezyc = grawitacja_ziemia / 6.0;

void pisanie_binarnie()
{
    int a = -58, b = a >> 0b11, c = -315;
    std::cout << "a = " << std::bitset<8>(a) << std::endl;
    std::cout << "b = " << std::bitset<8>(b) << std::endl;
    std::cout << "c = " << std::bitset<8>(c) << std::endl;
}

// referencja - alias do istniejacej zmiennej
// - nie wspieraja arytmetyki, nie moga byc NULL
void referencje()
{
    int x = 4, y = 5;
    int &r = x;
    std::cout << r++;
}

void stringi()
{
    std::string text("moj_tekst");
    std::string powtorzony("a", 10);
    std::cout << powtorzony.size() << std::endl;
}

void pary()
{
    std::pair<int, float> p(51, 3e-4);
    auto q = std::make_pair(53, "witaj");
    std::cout << p.first << ": " << p.second << std::endl;
    std::cout << q.first << ": " << q.second << std::endl;

}

// stos - pamiec zarzadzana przez program
//      - zmienne automatyczne usuwane po wyjsciu z bloku
// sterta - pamiec zarzadzana przez programiste
//        - alokowanie pamieci przez new, zwalnianie przez delete

void bledy()
{
    try
    {
        throw std::domain_error("out of domain!");
    }
    catch (const std::exception& e)
    {
       std::cerr << "caught: " << e.what() << std::endl;
       std::cerr << "type: " << typeid(e).name() << std::endl;
    }
    throw std::invalid_argument("your argument is invalid!");
    throw std::length_error("exceeded max lenght!");
    throw std::out_of_range("out of range!");
}

int main(int argc, char* argv[])
{
    wejscie_wyjscie();
    pisanie_binarnie();
    referencje();
    pary();
    bledy();
    return 0;
}