#include <iostream>

// programowanie obiektowe - paradygmat programowania, w ktorym programy
// definiuje sie za pomoca obiektow - elementow łączących stan i zachowanie
// - sklada sie z czterech paradygmatyow:

// 1 - abstrakcja
//   - kazdy obiekt w systemie jest modelem abstrakcyjnego wykonawcy
//   - moze wykonywac prace, opisywac i zmieniac swoj stan oraz komunikowac sie
//   - ukryta jest konkretna implementacja

// 2 - hermatyzacja (enkapsulacja)
//   - zamkniecie w obiekcie danych i funkcji składowych do operowania
//   - ukrywanie implementacji - zapewnia ze tylko wlasne metode sa uprawnione do zmiany stanu
//   - obiekt ma swoj interfejs ktory okresla dopuszczalne metody wspolpracy

// 3 - dziedziczenie
//   - pozwala na tworzenie nowych klas na podstawie istniejacych
//   - umozliwia ponowne uzycie kodu i ulozenie hierarchii

// 4 - polimorfizm
//   - pozwala na uzywanie obiektow roznych klas w sposob jednorodny
//   - realizowane przez funkcje wirtualne

// KLASA - typ zdefiniowany przez programiste
//       - jest modelem zawierajacym pola i metody

// KOMPOZYCJA - budowanie nowej klasy w oparciu o obiekty innych klas

// deklaracje w plik .hpp
class Point 
{
    // jezeli nie ma specyfikatora - private

    private: // widoczne tylko w klasie i jej funkcjach skladowych
        double x, y;

    public: // widoczne w klasie i poza klasa
        Point() = default; // konstruktor domyślny
        Point(double a, double b); // konstruktor zdefiniowany
        ~Point(); // destruktor
        void move_x(double dx);
        double distance(Point &p);

    protected: // widoczne tylko w klasie i klasach pochodnych

};

// definicje funkcji w .cpp razem 
void Point::move_x(double dx) // :: to operator zakresu
{
    x += dx;
}

// KONSTRUKTOR - metoda uruchamiana podczas inicjalizacji obiektu
//             - automatycznie nadaje poczatkowy stan 
//             - taka sama nazwa jak klasa!
//             - mozna przeciązyc - taka sama nazwa, inne argumenty
Point::Point(double x, double y) : x(x), y(y) {}
// prefereowany syntax - lista inicjalizyjna
// jezeli w klasie sa pola stale const mozna je zainicjalizowac tylko tak:
// ClassName::ClassName(parameters) : member1(value1), member2(value2), ... {}

// DESTRUKTOR - metoda uruchamiana tuz przed likwidacja obiektu
//            - zwalnia zasoby obiektu, informuje
Point::~Point() {
    std::cout << "Destroying point (" << x << ", " << y << ")\n";
}

class Range
{
    const int MIN, MAX; // pola stałe
    mutable int log_count; // pola ktore mozna modyfikowac nawet w funkcji const

    public:
        int min() const;
        int max() const;
};

int main()
{
    // tworzenie obiektu na stosie (stack)
    Point a = Point(4, 6);
    Point *q = &a;
    Point b(2, 3);

    // tworzenie obiektu na stercie (heap)
    Point* p = new Point(1, 2);
    delete p;

    // operator dostepu do skladowych: 
    // . dla obiektow, -> dla wskaznikow
    a.move_x(10); 
    q -> move_x(10);

    // THIS - wskaznik bedacy parametrem kazdej instancji funkcji skladowej
    //      - pokazuje ja biezacy obiekt
    //      - uzywany tylko w instacyjnych funkcjach skladowych i konstruktorach

    int c = 7, d = 5;
    // wskaźnik do stałej
    const int *p_to_const = &c;
    // (*p) = 12; niedozwolone bo stała
    p_to_const = &d;

    // staly wskaznik
    int *const p_const = &c;
    // p = &d; niedozwolone bo staly wskaznik
    (*p_const) = 12;

    

    return 0;
}
