
// RZUTOWANIE - zmiana typu danej lub zmiana interpretacji danych

// JAWNA KONWERSJA - niebezpieczna
// (int)3.1415926 - forma rzutowania
// double(7*11+5) - forma konstruktorowa (lepsza)

// NIEJAWNA KONWERSJA
// const double e = 2.718;
// int x = (int)e;
// double y = 2 * x+1; 

// EXPLICIT - zabrania uzywac danej funkcji do niejawnej konwersji

class zespolona 
{
    double re, im;
public:
    zespolona (double r=0, double i=0);
};

// STATIC_CAST - dziala na etapie kompilacji 
//             - static_cast<typ>(wyrażenie)
//             - konwersja podstawowywch typow liczbowych
//             - konwersja typu wyliczeniowego (enum) do calkowitego (np int)
//             - rzutowanie w gore/dol w hierarchii dziedziczenia 

// CONST_CAST - pozwala dodac/usunac deklarator const lub volatile w typie wyrazenia
//            - const_cast<typ>(wyrażenie), typ to wskaznik, referencja lub wskaznik do skladowej
//            - dziala na etapie kompilacji 

// REINTERPRET_CAST - zmienia interpretacje typu wyrazenia
//                  - tworzy wartość nowego typu, który ma ten sam wzorzec bitowy co podane wyrażenie
//                  - reinterpret_cast<typ>(wyrażenie)
int main()
{
    zespolona a;
    zespolona b = zespolona(1.2); // jawna konwersja
    zespolona c = 3.4; // niejawna konwersja
    zespolona d = (zespolona)5.6; // rzutowanie
    zespolona e = static_cast<zespolona>(7.8);
    zespolona f(9.0, 0.9);
}
