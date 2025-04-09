
// Do drzewa BST (na początku pustego) wstawiane są elementy 1, 2, 3, 4, 5, 6, 7.
// Podaj kolejność wstawiania elementów, przy której drzewo będzie miało największą/najmniejszą możliwą wysokość

// najwieksza wysokosc: 1, 2, 3, 4, 5, 6, 7 lub 7, 6, 5, 4, 3, 2, 1 - wysokosc 7
// najmniejsza wysokosc: 4, 2, 1, 3, 6, 5, 7 - wysokosc 3

// Odpowiedź uzasadnij i uogólnij na przypadek ciągu liczb 1, 2, . . . , 2^k–1 dla dowolnego naturalnego k > 1.

// najwieksza: 2^k - 1: wypisywanie po kolei od 1 do 2^k - 1
// najmniejsza: k: zaczecie od mediany (2^(k-1)), a potem kolejne mediany z zakresy liczb rodzielnego przez poprzednia mediane
// czyli za kazdym razem (2^k-1) 