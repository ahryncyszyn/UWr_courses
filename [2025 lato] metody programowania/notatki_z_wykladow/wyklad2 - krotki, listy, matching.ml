(*------------------------------- REKURENCJA -------------------------------*)
(* petla nieskoczona *)
let rec loop () = loop ();;

(* silnia rekurencyjnie *)
let rec fact n = (* funkcja rekurencyjna musi miec rec i nazwe *)
  if n = 0 then 1
  else n * fact (n - 1);;

(* rekurencja ogonowa - oszczedza pamiec bo nie potrzebuje nowych stack frames *)
(* kiedy nie wykonujemy zadnych obliczen na wyniku wywolania rekurencyjnego *)
let fact_iter n =
  let rec it n acc =
    if n = 0 then acc
    else it (n - 1) (acc * n)
  in it n 1;;

(*------------------------------- KROTKI -------------------------------*)
(1, 2, 3);;
(1, "foo", true);; (* moga miec rozne typy *)
let p = (1, "foo");;
fst p;; (* działa tylko dla par *)
let a, b, c = (1, "foo", true);; (* mozna szybko deklarowac zmienne *)


(*------------------------------- TYP OPTION -------------------------------*)
(* wskazujE na obecnosc jakiegos lub zadnego typu bezpiecznie *)
(* alternatywa ze wzgledu na brak null *)
(* jest konstruktorem - tworzy nowy typ t option dla typu t *)
type 'a option = None | Some of 'a;;
let o1 = Some 42;; (* tworzy int option *)
match o1 with Some x -> x | None -> 0;;

let rec list_max xs =
  match xs with
  | [] -> None
  | h :: t ->
      match list_max t with
        | None -> Some h
        | Some m -> Some (max h m);;

let safe_divide a b =
  if b = 0 then None (* bezpieczne zwracanie *)
  else Some (a / b);;

(* MATCHING *)
let z = 
  match "foo" with 
  | "bar" -> 0
  | _ -> 1;; (* _ oznacza cokolwiek innego *)

let z =
  match ["abc"; "def"; "ghi"] with
  | [] -> "empty"
  | h :: t -> h;; (* dzieli liste na glowe i reszte, zwraca głowe (pierwszy element) *)
  (* nie pozwala zwrocic t bo nie zgadza sie typ, ale wystarczy zamienic na ["empty"] *)


(*------------------------------- LISTY -------------------------------*)
[1; 2; 3];;
[true; false];; (* elementy moga byc jakiegokolwiek typu *)
(0 :: [1; 2; 3]);; (* dodaje element na poczatku listy *)

(* zwracanie głowy listy *)
let list_hd xs = 
  match xs with
  | [] -> failwith "list_hd"
  | x :: _ -> x

List.hd [1; 2; 3];;  (* funkcja wbudowana *)

(* zwracanie n-tego elementu listy *)
let rec nth xs n =
  if n = 0
  then List.hd xs
  else nth (List.tl xs) (n - 1)

(* sumuje elementy listy *)
let rec sum lst =
  match lst with
  | [] -> 0
  | h :: t -> h + sum t

(* ta sama funkcje ale inne nazwenictwo *)
let rec sum xs =
  match xs with
  | [] -> 0
  | x :: xs' -> x + sum xs'

(* dolączanie jednej listy do drugiej - mozna tez uzyc @ *)
let rec append lst1 lst2 =
  match lst1 with
  | [] -> lst2
  | h :: t -> h :: append t lst2

(* odwracanie listy *)
let reverse xs =
  let rec it xs ys =
    match xs with
    | [] -> ys
    | x :: xs -> it xs (x :: ys)
  in it xs []

(* insertowanie elementu *)
let rec insert y xs =
  match xs with
  | [] -> [y]
  | x :: xs' -> if y < x
    then y :: xs
    else x :: insert y xs'

(* sortowanie*)
let insertion_sort xs =
  let rec it xs ys =
    match xs with
    | [] -> ys
    | x :: xs' -> it xs' (insert x ys)
  in 
  it xs []

(* 
listy sa niemutowalne!!
cos co wyglada jak modyfikowanie listy tak naprawde tworzy nowa liste
fragmenty ktore moga byc dzielone, sa dzielone
ale nadal moga powstawac nieuzytki, czyli fragmenty pamieci
do ktorej juz nie mozna sie odnieśc wiec jest bezuzyteczna
*)


  
