
(* Zaimplementuj sortowanie przez wstawianie. Następnie pokaż, że wynikowa
lista jest posortowana niemalejąco. *)

let rec insert x xs =
  match xs with
  | [] -> [x]
  | y :: ys -> if x <= y then x :: xs else y :: insert x ys

let rec insertion_sort xs =
  match xs with
  | [] -> []
  | x :: xs -> insert x (insertion_sort xs)

let rec niemalejaco xs =
  match xs with
  | [] -> true
  | [_] -> true
  | x :: y :: rest -> x <= y && niemalejaco (y :: rest)

(*

lemat 1: niemalejaco(insert x' xs), gdzie xs juz jest posortowana
baza: niemalejaco(insert (x' [])) = niemalejaco([x']) = true
krok: zalozmy ze spelnione jest niemalejaco(insert x' xs)
      pokazemy ze niemalejaco(insert x x::xs)
1) x' <= x
niemalejaco(insert x' x::xs) = niemalejaco(x' :: x :: xs)
- posortowane, bo x' <= x

2) x' > x
niemalejaco(insert x' x::xs) = niemalejaco(x :: insert x' xs) 
= x <= x' && niemalejaco(insert x' xs) = true (z zal.ind)

teza: niemalejaco (insertion_sort xs)
baza: [] - niemalejaca trywialnie
krok: załozmy ze spelnione jest niemalejaco (insertion_sort xs)
      pokazemy ze spelnione jest rowniez niemalejaco (insertion_sort x::xs)

niemalejaco(insertion_sort x::xs) 
= niemalejaco(insert x (insertion sort xs)) (zal. ind)
= niemalejaco(insert x ys) (z lematu 1)

*)