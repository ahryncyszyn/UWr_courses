## Definicje

- **asercja** – warunek logiczny, który musi być spełniony w danym momencie obliczeń.
- **warunek końcowy** – asercja opisująca stan po wykonaniu programu.
- **warunek początkowy** – asercja opisująca stan przed wykonaniem programu.
- **wpecyfikacja** – warunek początkowy **+** warunek końcowy.

## Poprawność programów
- **własność stopu** – jeśli spełniony jest warunek początkowy, to obliczenie kończy się bez błędów.
- **częściowa poprawność** – jeśli obliczenie kończy się bez błędów, to spełniony jest warunek końcowy.
- **całkowita poprawność** – częściowa poprawność + własność stopu.

## Trójka Hoare’a
` {warunek_początkowy} P {warunek końcowy} `

## Reguły
- reguła skip 
    - pusta instrukcja nie zmienia stanu programu
$$
\frac{}{\{P\} \; \text{skip} \; \{P\}}
$$

- reguła przypisania 
    - kazdy predykat zachodzacy dla E przed przepisaniem, zachodzi rowniez dla x po przypisaniu
    - P jest asercją z wolnym wystąpieniem x
    - P\[E/x\] jest asercją z wyrazeniem E podstawionym pod x
$$
\frac{}{\{P[E/x]\} \; x := E \; \{P\}}
$$

- reguła złozenia
    - jezeli warunek koncowy Q jednej instrukcji jest taki sam jak warunek koncowy drugiej to mozna jest złozyć
$$
\frac{\{P\} \; S \; \{Q\} \quad , \quad \{Q\} \; T \; \{R\}}
     {\{P\} \; S;T \; \{R\}}
$$

- reguła warunku 
    - jezeli warunek koncowy Q jest wspolny dla czesci then (S) i else (T) wyrazenia to jest rowniez spelniony po calym wyrazeniu if else then
    - B nie moze miec efektów ubocznych
$$
\frac{\{B \wedge P\} \; S \; \{Q\} \quad , \quad \{\neg B \wedge P\} \; T \; \{Q\}}
{\{P\} \; \texttt{if} \; B \; \texttt{then} \; S \; \texttt{else} \; T \; \texttt{endif} \; \{Q\}}
$$

- reguła konsekwencji
    - pozwala osłabić warunek początkowy i/lub wzmocnić warunek końcowy
$$
\frac{P_1 \rightarrow P_2 \quad , \quad \{P_2\} \; S \; \{Q_2\} \quad , \quad Q_2 \rightarrow Q_1}
{\{P_1\} \; S \; \{Q_1\}}
$$

- reguła petli while
    - P jest niezmiennikiem petli, który jest zachowany przez ciało S
    - jezeli petla sie skonczyla to warunek petli B juz nie zachodzi
    - B nie moze miec efektów ubocznych
$$
\frac{\{P \wedge B\} \; S \; \{P\}}
{\{P\} \; \texttt{while} \; B \; \texttt{do} \; S \; \texttt{done} \; \{\neg B \wedge P\}}
$$

# Przykłady

# Niezmiennik pętli I

- na wejściu do petli I jest spełnione
- jezeli I jest prawdziwe przed iteracja to jest równiez prawdziwe po iteracji
- po zakonczeniu petli i spelnieniu warunku stopu B daje warunek koncowy  ($ I \wedge \neg B \rightarrow Post $)

# Zadania z list
> udowodnij poprawnosc algorytmu szybkiego potegowania korzystając z logiki Hoare'a

```
P = {x = x0 ∧ n = n0 ∧ n ≥ 0}
z := 1;
while (n > 0) 
{
  if (n % 2 == 1)
    z := z * x;
  n := n / 2;
  x := x * x;
}
{z = x^n}
```
![alt text](image-2.png)

- niezmiennik petli: $ I: \quad z \cdot x^n = x_0^{n_0} \wedge (n ≥ 0) $
- przed wejsciem do petli: 
  - załozenia: $x = x_0, \quad n = n_0, \quad n ≥ 0 \quad z = 1 $
  - $ z \cdot x^n = z \cdot x_0^{n_0} = x_0^{n_0}$
- po iteracji petli (dla n % 2 == 1): 
  - zalozenia: $z \cdot x^n = x_0^{n_0}, \quad n ≥ 0$
  - po iteracji: $z' = z \cdot x, \quad n' = n / 2 , \quad x' = x \cdot x$
  - $ z' \cdot x'^{n'} = z \cdot x \cdot (x \cdot x)^{n/2} = z \cdot x^{n}  $
- po iteracji petli (dla n % 2 == 0): 
  - zalozenia: $z \cdot x^n = x_0^{n_0}, \quad n ≥ 0$
  - po iteracji: $z' = z, \quad n' = n / 2 , \quad x' = x \cdot x$
  - $ z' \cdot x'^{n'} = z \cdot (x \cdot x)^{n/2} = z \cdot x^{n}  $
- po wyjsciu z petli:
  - $n = 0$
  - z niezmiennika: $z \cdot x^0 = z = x_0^{n_0}$
```
{x = x0 ∧ n = n0 ∧ n ≥ 0} (P0)
z := 1;
{ P0 ^ (z == 1)}
{ n0 > 0 ^ z * x^n = x0^n0} (P)
while (n > 0) 
{
  { P ^ n > 0 }
  if (n % 2 == 1)
    z := z * x;
  n := n / 2;
  x := x * x;
}
{ P ^ (n == 0) ^ z = x0^n0 }
```