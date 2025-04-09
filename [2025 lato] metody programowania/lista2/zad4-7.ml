
(* zad 4 - sprawdzanie czy element x znajduje sie w liscie *)
let rec mem x lst =
  match lst with
  | [] -> false
  | h :: t -> if h = x then true
              else mem x t;; 

(* zad 5 - znajdywanie najwiekszego elementu w liscie floatow *)
let rec maximum lst = 
  match lst with
  | [] -> neg_infinity (* narzuca ze fukncja zwraca float *)
  | h :: t -> max h (maximum t);;

(* zad 6 - wypisywanie wszystkich sufiksow listy *)
let rec suffixes lst = 
  match lst with
  | [] -> [[]]
  | h :: t -> lst :: suffixes t;;

(* zad 7 - sprawdzanie czy lista jest posortowana niemalejaco *)
let rec is_sorted lst =
  match lst with
  | [] | [_] -> true
  | h :: next :: t -> (h <= next) && is_sorted (next :: t);;
