(* funkcje wyzszego rzędu - przyjmują i zwracają inne funkcje *)
(* pozwalają na zwiększenie abstrakcji kodu poprzez wyizolowanie powtarzających się schematow *)

(* wiecej o sortowaniu *)
let rec insert y xs =
  match xs with
  | [] -> [y]
  | x :: xs' -> if y < x
    then y :: xs
    else x :: insert y xs';;

(* val insert_generic : ('a -> 'a -> bool) -> 'a -> 'a list -> 'a list = <fun> *)
let rec insert_generic lt y xs =
  match xs with
   | [] -> [y]
    | x :: xs' -> if lt y x
      then y :: xs
      else x :: insert y xs';;

(* currying (rozwijanie funkcji) - zamiast przyjmowac kilka argumentow, pobiera kazdy argument jako nowa funkcja *)
(* pozwala na zdefiniowanie nowych funkcji: *)
let insertion_sort_new = insert_generic (<);;
(* val insertion_sort_new : '_weak1 list -> '_weak1 list = <fun> *)
(* '_weak110 - osłabiona zmienna typu, bedzie zmieniona przy pierwszym uzyciu *)

(*------------------------------- ŁĄCZENIE W POTOK: |> -------------------------------*)
(* przekazuje argument do funkcji *)
(* x |> f = f x *)
let double x = 2 * x;;
let x = 5 |> double;; (* val x : int = 10 *)
let rec ( -- ) i j = (* tworzy liste liczb po kolei *)
  if i > j then [] 
  else i :: i + 1 -- j;; 
let square x = x * x
let sum = List.fold_left ( + ) 0

(* oblicza sume kwadratow zakresu liczb *)
let sum_sq n =
  0 -- n              (* [0;1;2;...;n]   *)
  |> List.map square  (* [0;1;4;...;n*n] *)
  |> sum              (*  0+1+4+...+n*n  *)

(*------------------------------- MAP -------------------------------*)
(* pozwala zaaplikowac jakas funkcje do całej listy *)
let rec map f xs =
  match xs with
  | [] -> []
  | x::xs -> (f x) :: map f xs;;
(* val map : ('a -> 'b) -> 'a list -> 'b list = <fun> *)

let add1 x = x + 1;;
map add1 [1; 5; 3];; (* int list = [2; 6; 4] *)
map string_of_int [1; 5; 3];; (* string list = ["1"; "5"; "3"] *)
map (fun x -> x * 2 - 3) [1;5;3];; (* int list = [-1; 7; 3] *)
map (map add1) [[1;2];[4;7]];; (* int list list = [[2; 3]; [5; 8]] *)

(*------------------------------- FILTER -------------------------------*)
(* pozwala wyeliminowac elementy na podstawie warunku *)
let rec only_nonempty xs =
  match xs with
  | [] -> []
  | x::xs -> if x <> [] then x :: only_nonempty xs else only_nonempty xs;;

(* p jak predicate *)
let rec filter p xs =
  match xs with
  | [] -> []
  | x::xs -> if p x then x :: filter p xs else filter p xs;;
(* val filter : ('a -> bool) -> 'a list -> 'a list = <fun> *)

(* wersja z rekursja ogonowa *)
let rec filter_aux p acc xs = 
  match xs with
  | [] -> List.rev acc (* na koniec odwracamy wynik bo byl budowany odwrotnie *)
  | h :: t -> if p h then filter_aux p (h :: acc) t else filter_aux p acc t
let filter p = filter_aux p [];;

filter (fun x -> x > 0) [1; 2; -3; 1; -9; 2];; (* int list = [1; 2; 1; 2] *)
filter (fun x -> x mod 2 = 0) [1; 2; -3; 4; 8;];; (* int list = [2; 4; 8] *)
filter (fun x -> x mod 2 = 0 && x < 0) [1; -2; -3; 4; 8;];; (* int list = [-2] *)

(*------------------------------- FOLDR, FOLDL -------------------------------*)
(* kumuluje informacje z całej listy *)
(* foldr i foldl roznia sie kierunkiem ewaluowania argumentow *)
(* foldl uzywa rekursji ogonowej, foldr nie *)
let rec fold_right f xs a =
  match xs with
  | [] -> a
  | x::xs -> f x (fold_right f xs a);;
(* val fold_right : ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b = <fun> *)

let new_append xs ys = fold_right (fun x xs -> x :: xs) xs ys;;
(* val new_append : 'a list -> 'a list -> 'a list = <fun> *)
new_append [1;2] [3;4];; (* int list = [1; 2; 3; 4] *)

let new_map f xs = fold_right (fun x xs -> f x :: xs) xs [];;
new_map add1 [1;2;3];; (* int list = [2; 3; 4] *)

let new_filter p xs = fold_right (fun x xs -> if p x then x :: xs else xs) xs [];;
new_filter (fun x -> x > 0) [1; -2; 3; 5; -3];; (* int list = [1; 3; 5] *)

let length xs = fold_right (fun _ y -> 1 + y) xs 0;;
length [5; 2; 4];; (* int = 3 *)

let rec fold_left f acc xs =
  match xs with
  | [] -> acc
  | x :: xs' -> fold_left f (f acc x) xs'

let new_length xs = fold_left (fun acc _ -> acc + 1) 0 xs;;
new_length [5; 2; 4];; (* int = 3 *)

let weird_map f xs = fold_left (fun xs x -> f x :: xs) [] xs;;
weird_map (fun x -> x + 1) [1; 2; 3];; (* int list = [4; 3; 2] *)

(*------------------------------- PORÓWNYWANIE -------------------------------*)
let pair_lex (a1, a2) (b1, b2) =
  a1 < b1 || a1 = b1 && a2 < b2;;
(* val pair_lex : 'a * 'b -> 'a * 'b -> bool = <fun> *)
(* nie ma currying bo () definiuje krotke *)

let pair_lex_generic lt1 lt2 (a1, a2) (b1, b2) =
  lt1 a1 b1 || a1 = b1 && lt2 a2 b2;;
(* ('a -> 'a -> bool) -> ('b -> 'c -> bool) -> 'a * 'b -> 'a * 'c -> bool = <fun> *)

(* = vs == *)
(* = to porownanie strukturalne --> czy wartosci sa logicznie takie same? *)
new_append [1;2] [3;4] = [1;2;3;4];; (* true *)
(* == to porownanie fizyczne --> czy wartosci sa tym samym obiektem w pamieci? *)
new_append [1;2] [3;4] == [1;2;3;4];; (* false *)

let xs = new_append [1;2] [3;4];;
let ys = new_append [0] xs;;
List.tl ys = xs;; (* true *)
List.tl ys == xs;; (* true *)

(*------------------------------- TYPY WARIACYJNE -------------------------------*)
(* rodzaje konstruktorow + argumenty ktore przyjmuja *)
type int_or_string = 
  | IntVal of int 
  | StringVal of string;;
IntVal 5;; (* int_or_string = IntVal 5 *)

let string_of_int_or_string x =
  match x with
  | IntVal a -> string_of_int a
  | StringVal s -> s;;
(* val string_of_int_or_string : int_or_string -> string = <fun> *)

(*------------------------------- DRZEWA -------------------------------*)
(* Leaf - pusty lisc, Node - lewe dziecko, wartosc, prawe dziecko *)
type 'a tree =
  | Leaf 
  | Node of 'a tree * 'a * 'a tree;;
let ex_tree = Node (Node (Leaf, 1, Leaf), 2, Node (Leaf, 3, Leaf));;

let rec map_tree f t =
  match t with
  | Leaf -> Leaf
  | Node (l, v, r) -> Node (map_tree f l, f v, map_tree f r);;
(* val map_tree : ('a -> 'b) -> 'a tree -> 'b tree = <fun> *)
map_tree (fun x -> x + 1) ex_tree;; (* int tree = Node (Node (Leaf, 2, Leaf), 3, Node (Leaf, 4, Leaf)) *)

let rec sum_tree t =
  match t with
  | Leaf -> 0
  | Node (l, v, r) -> sum_tree l + v + sum_tree r;;
(* val sum_tree : int tree -> int = <fun> *)
sum_tree ex_tree;; (* int = 6 *)

let rec fold_tree f acc t =
  match t with
  | Leaf -> acc
  | Node (l, v, r) -> f (fold_tree f acc l) v (fold_tree f acc r);;
(* val fold_tree : ('a -> 'b -> 'a -> 'a) -> 'a -> 'b tree -> 'a = <fun> *)
fold_tree (fun vl v vr -> vl + v + vr) 0 ex_tree;; (* int = 6 *)

let size t = fold_tree (fun l _ r -> 1 + l + r) 0 t
let depth t = fold_tree (fun l _ r -> 1 + max l r) 0 t
let preorder t = fold_tree (fun l x r -> [x] @ l @ r) [] t

let rec find_bst x t =
  match t with
  | Leaf -> false
  | Node (l, v, r) ->
      if v = x then true
      else if v < x then find_bst x r else find_bst x l;;
(* val find_bst : 'a -> 'a tree -> bool = <fun> *)
find_bst 1 ex_tree;; (* true *)
find_bst 5 ex_tree;; (* false *)

let rec insert_bst x t =
  match t with
  | Leaf -> Node (Leaf, x, Leaf)
  | Node (l, v, r) ->
      if x = v then t
      else if v < x then Node (l, v, insert_bst x r)
      else Node (insert_bst x l, v, r);; 
(* val insert_bst : 'a -> 'a tree -> 'a tree = <fun> *)
insert_bst 4 ex_tree;; (* Node (Node (Leaf, 1, Leaf), 2, Node (Leaf, 3, Node (Leaf, 4, Leaf))) *)

let preorder_lin t =
  let rec pre_acc acc t =
    match t with
    | Leaf -> acc
    | Node (l, v, r) -> v :: (pre_acc (pre_acc acc r) l)
  in pre_acc [] t;;

(*------------------------------- CURRYING, UNCURRYING -------------------------------*)
let curry f x y = f (x, y)
(* val curry : ('a * 'b -> 'c) -> 'a -> 'b -> 'c = <fun> *)
let uncurry f (x, y) = f x y
(* val uncurry : ('a -> 'b -> 'c) -> 'a * 'b -> 'c = <fun> *)

(*------------------------------- DIAGRAMY PUDEŁKOWE -------------------------------*)
[1; 2; 3];; (* Reprezentacja w pamięci: (1 :: (2 :: (3 :: []))) *)
(* OCaml współdzieli struktury danych zamiast je kopiować!! *)
(* dane do których nie ma odniesień są zbierane przez GC (garbage collector) *)