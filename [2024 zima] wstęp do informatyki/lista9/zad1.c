
// zliczamy wywolania isfree(n − 1, y)
// udowodnic ze dla n >= 4 jest ich nie wiecej niz  (n/2 + 1) × n!

// dla n >= 4 istnieje rozwiazanie problemu n hetmanow
// wiec w kazdej kolumnie i kazdym rzedzie bedzie jeden hetman
// mozliwe rozwiazania sa symetryczne wzgledem pionowego i poziomego przeciecia

// wiec znajdzie rozwiazanie docierajac wczesnije niz do polowy pierwszej kolumny
// w pierwszej kolumnie maksymalnie (n+1)/2 * (n-1)! * n = (n/2 + 1/2) * n! 