#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

// WYJATEK - obiekt sygnalizujacy blad
//         - zglaszany przez throw

// THROW - zwija stos az do znalezienia odpowiedniego bloku catch
//       - obiekt wyjatku jest umieszczamy w pamieci globalnej (specjalne miejsce)
//       - likwidowany dopiero po wyjsciu z bloku catch

// WYJATKI W KONSTRUKTORZE - obiekt nie zostaje utworzony
//                         - trzeba najpierw zwolnic juz zalokowane zasoby
//                         - nie mozna

// THROW E, CATCH (H) - spelniony jezeli:
// - H jest tego samego typu co E
// - H jest jednoznaczną publiczną klasą bazową dla E
// - H i E są wskaźnikami, a dla typów na które wskazują zachodzi powyzsze
// - H jest referencją, a dla typu do którego się odnosi zachodzi powyzsze
// - H jest obiektem stałym, a dla typu do którego się odnosi zachodzi powyzsze

// jezeli funkcja rezerwuje jakis zasob (pamiec, strumien) i zglosi wyjatek to
// moze potem nie zwolnic tego zasobu
// rozwiazanie - zarzadzanie zasobami poprzez opakowanie ich klasami
//             - zasob rezerwowany w konstruktorze klasy
//             - zasob zwalniany w destruktorze klasy

class plik
{
    FILE *wsk;
public:
    plik (const char *naz, const char *atr)
    {
        wsk = fopen(naz,atr);
        if (!wsk) throw "brak_pliku";
    }
    
    ~plik () throw() { fclose(wsk); wsk = 0; }
    
    operator FILE* () noexcept { return wsk; }
};

// SHARED_PTR - klasa ktorej obiekty sa inicjalizowane wskaznikami
//            - mozna sie poslugiwac nim jak zwyklym wskaznikiem
//            - sam niszczy swoją zawartość jeśli nie ma już współdzielonych
//              wskaźników odnoszących się do obiektu początkowo
//              tworzonego dla współdzielonego wskaźnika
//            - zlicza liczbe referencji 
//         

struct C { int a; int b; };

// OPERACJA BEZPIECZNA - pozostawia program w prawidłowym stanie, gdy zgłosi wyjątek

// NOEXCEPT - specyfikator oznaczajacy ze funkcja nie zglasza wyjatkow
//          - kazdy destruktor (delete) jest domyslnie noexcept
//          - mozna tez tak wywolac new(nothrow), wtedy w przypadku niepowodzenia zwraca nullptr

// KONCZENIE PROGRAMU
// exit(int) - lagodny sposob, zamyka pliki itp
// abort() - drastyczny sposob, bez zamykania plikow itp
// terminate() - wywoluje abort()
//             - gdy niezlapano rzuconego wyjatku
//             - gdy rzucono wyjatek w trakcie obslugi innego wyjatku
//             - gdy rzucono wyjatek w funkcji noexcept

// WLASNE WYJATKI - warto dziedziczyc po exception
//                - trzeba zdefiniowac konstruktor domyślny, konstruktor kopiujący,
//                  przypisanie kopiujące, wirtualny destruktor oraz metodę what()

// ASERCJE - pozwala oznaczyc niezmienniki w programie
//         -  gdy warunek jest fałszywy to na cerr zostanie wypisany odpowiedni komunikat
//            o błędzie i program zostanie przerwany za pomocą funkcji abort()
//         - assert() lub static_assert(wyrazenie, blad)

int main()
{
    try
    {
        int x = 0;
        cerr << "integer (>0): ";
        cin >> x;
        if (!cin) throw "i/o error";
        if (x <= 0) throw x;
    }
    // wyjatki sa rozroznialne po typie
    catch (const char *ex)
    {
        cerr << "number format error" << endl;
    }
    catch (int ex)
    {
        cerr << "number value error" << endl;
    }

    // wskaznik shared_ptr
    shared_ptr<C> foo(new C);
    foo -> a = 10, foo -> b = 20;
    cout << "foo: " << (*foo).a << ' ' << (*foo).b << endl;

    // może zgłosić wyjątek bad_alloc
    int *p = new int[1000000];

    // nie zgłosi wyjątku, najwyzej nullptr
    if (int *q = new(nothrow) int[1000000])
    {
    // przydział się powiódł
    }
    else
    {
    // przydział nie powiódł się
    }
}