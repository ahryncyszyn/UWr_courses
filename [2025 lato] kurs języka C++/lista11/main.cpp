
#include "mylist.hpp"
using namespace std;
using namespace adt;

int main()
{
    mylist<int> l1;
    cout << "Konstruktor domyslny: " << l1 << endl;

    mylist<int> l2({1, 2, 3, 4, 5});
    cout << "Konstruktor z lista inicjalizacyjna: " << l2 << endl;

    mylist<int> l3({1, 1, 1, 1, 1});
    mylist<int> l4 = l3;
    cout << "Konstruktor kopiujacy: " << l4 << ", skopiowane z: " << l3 << endl;

    mylist<int> l5(std::move(l3));
    cout << "Konstruktor przenoszacy: " << l5 << ", przeniesiona z: " << l3 << endl;

    mylist<int> l6;
    l6 = l5;
    cout << "Przypisanie kopiujace: " << l6 << ", skopiowane z: " << l5 << endl;

    mylist<int> l7;
    l7 = std::move(l5);
    cout << "Przypisanie przenoszace: " << l7 << ", przeniesione z: " << l5 << endl;

    mylist<int> l8({7, 8});
    l8.insert_at_beginning(1);
    cout << "Dolaczenie elementu 1 na poczatku: " << l8 << endl;

    l8.insert_at_end(2);
    cout << "Dolaczenie elementu 2 na koncu: " << l8 << endl;

    l8.insert_at_position(2, 3);
    cout << "Dolaczenie elementu 3 na pozycji 2: " << l8 << endl;

    l8.delete_from_start();
    cout << "Usuniecie elementu z poczatku: " << l8 << endl;

    l8.delete_from_end();
    cout << "Usuniecie elementu z konca: " << l8 << endl;

    l8.delete_from_position(1);
    cout << "Usuniecie elementu z pozycji 1: " << l8 << endl;

    cout << "Usuwanie elemntow z niepoprawnej pozycji:" << endl;
    try
    {
        l8.delete_from_position(20);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        l8.delete_from_position(-5);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    mylist<int> l9({1, 1, 1, 2, 2, 2, 3, 3, 3});
    l9.delete_value_first(1);
    cout << "Usuwanie pierwszego wystapienia 1: " << l9 << endl;
    
    l9.delete_value_all(2);
    cout << "Usuwanie kazdego wystapienia 2: " << l9 << endl;

    int res = l9.find_position(3);
    cout << "Znalezienie pozycji 3 w " << l9 << ": " << res << endl;

    cout << "Szukanie pozycji liczby ktorej nie ma w liscie:" << endl;
    try
    {
        l8.find_position(8);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "Liczba wystapien 3: " << l9.count_value(3) << endl;
    cout << "Liczba elementow " << l9 << ": " << l9.count_all() << endl;
    cout << "Czy jest pusta? " << l9.is_empty() << endl;

}