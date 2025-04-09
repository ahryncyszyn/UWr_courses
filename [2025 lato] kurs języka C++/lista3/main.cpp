#include "punkt.hpp"
#include "kolejka.hpp"
using namespace std;

int main() {
    cout << "Konstruktor z zadana pojemnoscia\n";
    kolejka k1(5);
    k1.print();

    cout << "Konstruktor delegatowy\n";
    kolejka k2;
    k2.print();

    cout << "Konstruktor z lista inicjalizacyjna\n";
    kolejka k3 = {punkt(1, 2), punkt(2, 3), punkt(3, 4)};
    k3.print();

    cout << "Konstruktor kopiujący\n";
    k1.wstaw(punkt(5, 5));
    kolejka k4 = k1;
    k4.print();

    cout << "Konstruktor przenoszący\n";
    kolejka k4_moved = std::move(k3);
    k4_moved.print();
    cout << "Kolejka ktora została przeniesiona:\n";
    k3.print();

    cout << "Operator przypisania kopiującego\n";
    kolejka k5(5), k6(3);
    k6.wstaw(punkt(9, 10));
    k6.print();
    k5 = k6;
    k5.print();

    cout << "Operator przypisania przenoszącego\n";
    kolejka k7(3);
    k7.wstaw(punkt(11, 12));
    k7.print();
    k7 = std::move(k6);
    k7.print();

    cout << "Tworzenie kolejki o pojemności 3\n";
    kolejka k8(3);
    k8.print();

    cout << "Wstawianie 3 punktów do kolejki\n";
    k8.wstaw(punkt(1, 2));
    k8.wstaw(punkt(3, 4));
    k8.wstaw(punkt(5, 6));
    k8.print();

    try
    {
        cout << "Wstawianie 4-tego elementu do kolejki 3-elementowej\n";
        k8.wstaw(punkt(7, 8));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    
    try
    {
        cout << "Podgladanie elementu z przodu\n";
        k8.zprzodu().print();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    cout << "Dlugosc kolejki: " << k8.dlugosc() << endl;

    cout << "\n\nUsuwanie 3 elementów z kolejki\n";
    k8.usun();
    k8.usun();
    k8.usun();
    k8.print();

    try
    {
        cout << "Usuwanie z pustej kolejki\n";
        k8.usun();
    } catch (const exception& e) 
    {
        cerr << e.what() << endl;
    }
    
    return 0;
}