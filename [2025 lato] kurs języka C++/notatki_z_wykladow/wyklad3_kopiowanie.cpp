
#include <iostream>
using namespace std;

// STATIC - składowe powiązane z klasa a nie samym obiektem
//        - tworzone jednokrotnie w pamięci i dzielone
//        - istnieje w pamięci nawet gdy nie ma zadnego obiektu danej klasy
//        - nie mają dostępu do niestatycznych metod i zmiennych
class myclass
{
public:
    int myVar; 
    static int myStaticVar;
    static void StaticFunc()
    {
        // dostep tylko do zmiennych static
        cout << myStaticVar; 
    };
};

void inicjalizacja_typow_podstawowych()
{
    // inicjalizacja zmiennej za pomoca formy konstruktorowej
    // to pozwala tworzyc liste inicjalizacyjna w konstruktorach klas
    int x(11);
    double y(3.14/2);
    cout << x << y << endl;

    // konstruktor domyslny nadaje warotsc domyslna
    bool b = bool(); 
    char c = char();
    cout << b << c << endl;
}

// KONSTRUKTOR DELEGUJACY - wywoluje inny konstruktor
class example
{
    int x, y;
public:
    example(int a, int b) : x(a), y(b) {};
    example(int a) : example(a, 0) {}; 
};

class derived : public example
{
public:
    int z, sum;
    // wowołuje konstruktor klasy bazowej
    derived(int a, int c) : example(a), z(c), sum(0) {};
    derived(initializer_list<int> values) : example(0), z(0), sum(0)
    {
        sum = 0;
        for (int val : values) sum += val;
    }
};

// REFERENCJA - alias dla istniejacej zmiennej
//            - pozwala na przekazanie wartości do funkcji bez kopiowania
void ref_do_stalej(const string &msg)
{
    cout << "wiadomosc: " << msg << endl;
}

// L-WARTOSC - ma nazwe i istnieje w pamięci 
//           - np int a = 10;
// R-WARTOSC - tymczasowy obiekt bez nazwy 
//           - np 10+5, string("Hi")
// R-REFERENCJA - moze przechwycic r-wartosc i pozwolic na jej modyfikacje
//              - pomaga przy przenoszeniu zasobów zamiast kopiowania
class MemObj 
{  
    public: 
    void *Memory; // wskaźnik na dynamicznie alokowana pamięć

    MemObj() { Memory = nullptr; } // konstruktor domyślny

    // KONSTRUKTOR PRZENOSZACY - pozwala na incjalizowanie obiektu z innego (tymaczasowego) obiektu
    //                         - czysci tej inny obiekt do stanu poczatkowego
    MemObj(MemObj&& sObj)
    {
        // przejmuje pamiec obiektu tymczasowego
        Memory = sObj.Memory;
        sObj.Memory = nullptr; 
    } 

    // KOSTRUKTOR KOPIUJACY - pozwala przyporzadkowac nowe dane juz zainicjalizowanemu obiektowi
    //                      - nie modyfikuje tego drugiego obiektu
    MemObj& operator=(const MemObj &other) 
    {
        // unika samoprzypisania
        if (this != &other)
        {
            // zwalnia stara pamiec
            delete[] (Memory);

            // przydzielamy nową pamięć i kopiuje dane
            Memory = new char[strlen(static_cast<char*>(other.Memory)) + 1];
            strcpy(static_cast<char*>(Memory), static_cast<char*>(other.Memory));
        }
        return *this;
    }

    MemObj(int nBytes) 
    { 
        // alokuje nowa pamiec
        Memory = new char[nBytes]; 
    } 

    ~MemObj() { if (Memory != nullptr) delete[] Memory; } };

// RVO - return value optimisation
//     - jeżeli funkcja zwraca przez wartość obiekt roboczy stworzony
//       w ciele funkcji, to jest on tworzony w miejscu przeznaczonym
//       na wynik (pomijane jest kopiowanie)

int main()
{
    // statyczne składowe muszą byc zainicjalizowane poza definicją klasy
    // można mieć do nich dostęp nawet jak nie ma żadnych obiektów
    myclass::myStaticVar = 0;
    cout << myclass::myStaticVar; 
    // statyczne fukcje można wywołać bez żadnych obiektów
    myclass::StaticFunc();

    inicjalizacja_typow_podstawowych();

    derived d1 {1, 2, 3, 4, 5};
    cout << "Sum member of d1 object: " << d1.sum << endl;

    ref_do_stalej("tutaj jest wiadomosc!!");

    // MOVE() - rzutuje obiekt na r-wartość
    //        - nie przenosi danych samodzielnie!
    MemObj o1(50);
    MemObj o2 = std::move(o1);

    // konstruktor kopiujacy
    MemObj obj1(50), obj2;
    std::strcpy(static_cast<char*>(obj1.Memory), "Hello");
    obj2 = obj1;
    std::cout << "obj2.Memory: " << static_cast<char*>(obj2.Memory) << std::endl;

}