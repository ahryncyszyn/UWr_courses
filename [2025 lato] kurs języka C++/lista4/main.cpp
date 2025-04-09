#include "wielom.hpp"
using namespace std;

int main() 
{

    // Test domyślnego konstruktora
    wielom w1;
    cout << "Domyślny konstruktor (w1): " << w1 << endl;

    // Test konstruktora z podanym stopniem i tablicą współczynników
    double a[] = {1, 2, 3, 5};
    wielom w3(3, a);
    cout << "Konstruktor z podanym stopniem i tablicą współczynników (w3): " << w3 << endl;
    
    // Test konstruktora z blednym stopniem wielomianu
    double b[] = {1, 2, 3, 4, 5};
    try
    {
        wielom w_bledny_st(-2, b);
        cout << "ujemny stopien powinien zwracac blad:" << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // Test konstruktora z zerowym wspolczynnikiem przy najwyzszej potedze
    double c[] = {1, 2, 3, 0};
    try
    {
        wielom w_bledny_wsp(3, c);
        cout << "zerowy wspolczynnik przy max potedze powinien zwracac blad:" << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
       
    // Test konstruktora z listą inicjalizacyjną
    wielom w2{1, 2, 3, 4};
    cout << "Konstruktor z listą inicjalizacyjną (w2): " << w2 << endl;
         
    // Test konstruktora kopiującego
    wielom w4 = w3;
    cout << "Konstruktor kopiujący (w4, kopia w3): " << w4 << endl;
       
    // Test operatora przypisania
    w1 = w2;
    cout << "Operator przypisania (w1 = w2): " << w1 << endl;
       
    // Test dodawania wielomianów
    wielom w5 = w2 + w3;
    cout << w2 << " + " << w3 << " = " << w5 << endl;

    // Test dodawanie wielomianow ktory zmienia stopien wyniku
    wielom w6{1, 1, 1, 1};
    wielom w7{1, 1, 1, -1};
    cout << w6 << " + " << w7 << " = " << (w6 + w7) << endl;
       
    // Test odejmowania wielomianów
    wielom w8 = w2 - w3;
    cout << w2 << " - " << w3 << " = " << w8 << endl;
       
    // Test mnożenia wielomianów
    wielom w9 = w2 * w3;
    cout << w2 << " * " << w3 << " = " << w9 << endl;
       
    // Test mnożenia wielomianu przez skalar
    wielom w10 = w2 * 2.0;
    cout << w2 << " * skalar 2.0: " << w10 << endl;

    // Test obliczania wartości wielomianu
    double value = w2(2.0); // Oblicz wartość w2 dla x = 2.0
    cout << "Obliczenie wartości " << w2 << " dla x = 2.0: " << value << endl;

    // Test odczytu wspolczynnika
    cout << "Odczyt wspolczynnika przy x^3 dla " << w2 << " : " << w2[3] << endl;

    // Test odczytu wspolczynnika poza zakresem
    try
    {
        cout << "Odczyt wspolczynnika poza zakresem: " << w2[6];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // Test wczytywania wielomianu
    try
    {
        cout << "wczytywanie wielomianu z wejscia:" << endl;
        wielom do_wczytania;
        cin >> do_wczytania;
        cout << "pomyślnie wczytano wielomian: " << do_wczytania << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
       
    return 0;
}