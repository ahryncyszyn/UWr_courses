(*------------------------------- WAZNE FUNKCJE -------------------------------*)
let length xs =
  let rec it lst acc =
    match lst with
    | [] -> acc
    | _ :: t -> it t (acc + 1)
  in it xs 0;;

let rec append xs ys =
  match xs with
  | [] -> ys
  | h :: t -> h :: (append t ys)

let compose f g x = f (g x);;

let rec map f xs =
  match xs with
  | [] -> []
  | x :: xs' -> (f x) :: map f xs'

let rec filter p xs =
  match xs with
  | [] -> []
  | x :: xs' -> 
      if p x then x :: filter p xs'
      else filter p xs'

let rec fold_left f acc xs =
  match xs with
  | [] -> acc
  | x::xs' -> fold_left f (f acc x) xs'

let rec fold_right f xs acc =
  match xs with
  | [] -> acc
  | x :: xs' -> f x (fold_right f xs' acc)

let reverse xs =
  let rec aux acc lst = 
    match lst with
    | [] -> acc
    | h::t -> aux (h::acc) t
  in aux [] xs

(* ----------------------- ZAD1 - napisac funkcje ktora odpowiada danemu typowi *)
(* a -> b -> a *)
let funkcja1 a b = a;;

(* (a -> b -> c) -> (a -> b) -> a -> b *)
let funkcja2 f g a = f g a;;

(* ((a -> a) -> a) -> a *)
let funkcja3 f = f (fun a -> a);;

(* (a -> b) -> (a -> c) -> (a -> b * c) *)
let funkcja4 f g = (fun x ->(f x, g x))

(* (a -> (a * b) option) -> a -> b list *)
let rec funkcja5 f x = 
  match (f x) with 
  | None -> []
  | Some (a, b) -> b :: (funkcja5 f a)

(* (a -> b) -> (b -> c) -> a -> c *)
let funkcja6 f g a = g (f a)

(* a * (a -> b) -> b *)
let funkcja7 p = snd p (fst p)

(* ((a -> b) -> b) -> b *)
let rec funkcja8 f = f (fun x -> funkcja8 f)

(* ----------------------- ZAD2 - napisac typ danej funkcji *)

(* ('a -> 'b) -> 'a -> 'b *)
let app f x = f x;;

(* ('a -> 'b -> 'c) -> 'b -> 'a -> 'c *)
let flip f x y = f y x;;

(* (('a * 'b) -> c) -> ('a -> 'b -> 'c) *)
let curry f = (fun x -> (fun y -> f (x, y)));;

(* ('a -> 'b) -> ('c -> 'a) -> 'c -> b *)
let compose f g x = f (g x);;

(* brak typu! *)
(* let omega x = x x;;  *)

(* ('a -> bool) -> 'a -> bool -> bool *)
fun x y z -> x y && z;;


fun f x -> f (f x) && x > 0;;

(* ----------------------- ZAD3 - napisz funkcje ktora generuje wszystkie permutacje listy *)
let rec inserts x lst = 
  match lst with 
  | [] -> [[]]
  | h :: t -> 
      (x :: lst) :: (map (fun l -> h :: l) (inserts x t))

let rec permutations lst =
  match lst with 
  | [] -> [[]]
  | h :: t -> 
    List.flatten (List.map (inserts h) (permutations t))

(* ----------------------- ZAD4 - napisz funkcje za pomoca fold_left lub fold_right *)

let rec fold_right f xs acc =
  match xs with
  | [] -> acc
  | x::xs' -> f x (fold_right f xs' acc);;

let rec fold_left f acc xs =
  match xs with
  | [] -> acc
  | x :: xs' -> fold_left f (f acc x) xs'

(* zip *)
let zip xs ys =
  let helper (acc, rest_ys) x =
    match rest_ys with
    | [] -> (acc, [])
    | y :: ys' -> ((x, y) :: acc, ys')
  in
  let (zipped, _) = List.fold_left helper ([], ys) xs in
  List.rev zipped

(* maximum z listy int *)
let list_max xs = 
  match xs with 
  | [] -> failwith("empty list");
  | h::t -> fold_left max h t;;

(* filter *)
let new_filter p xs = 
  fold_right (fun x xs -> if (p x) then (x :: xs) else xs) xs [];;

(* map *)
let new_map f xs = 
  fold_right (fun x xs -> f x :: xs) xs [];;

(* reverse *)
let reverse xs = 
  fold_left (fun acc x -> x :: acc) [] xs;;

(* najwieszy element list z dodatnimi wartosciami *)
let max_element xs =
  fold_left max 0 xs;;

(* dodanie indeksow do elementow listy *)
let zip_with_index lst =
  let max_idx = List.length lst - 1 in
  let (result, _) = fold_right (fun x (acc, idx) -> ((idx, x) :: acc, idx - 1)) lst ([], max_idx)
in result;;

(* napisac fold_left za pomoca fold_right i na odwrot - akumulator musi byc funkcja *)
let fold_left f acc xs =
  fold_right (fun x g -> fun a -> g (f a x)) xs (fun x -> x) acc;;

let fold_right f xs acc =
  List.fold_left (fun g x -> fun a -> g (f x a)) (fun x -> x) (List.rev xs) acc

(* is_palindrome *)
let is_palindrome xs =
  let rev = List.fold_left (fun acc x -> x :: acc) [] xs in
  xs = rev

(* ----------------------- ZAD5 - zasady indukcji *)

(* 
Zasada indukcji dla liczb naturalnych:
dla każdej własności P,
jeśli P(0)
oraz dla każdego k naturalnego P(k) implikuje P(k+1)
to dla każdego n naturalnego zachodzi P(n) *)

type 'a my_list =
  | Nil
  | Cons of 'a * 'a my_list

(* 
Zasada indukcji dla: dla każdej własności P,
* jeśli zachodzi P([])
* oraz dla każdego x : 'a, xs : 'a list, P(xs) implikuje P(x :: xs)
* to dla każdej listy xs as zachodzi P(xs) 
*)

type nat = 
  | Zero
  | S of nat

(* 
Zasada indukcji: dla kazdej własności P, jezeli
* P zachodzi dla Z, czyli P(Z) oraz
* dla kazdego m naturalnego P(m) -> P(s(m))
* to dla kazdego n naturalnego zachodzi P(n)
*)

type 'a nonempty_list = 
  | Singleton of 'a
  | MyList of 'a * 'a nonempty_list
  
(* 
Zasada indukcji: Mając P
* dla kazdego x typu 'a zachodzi dla Singleton, czyli P(Singleton)
* dla kazdego xs typu 'a nonempty_list i dla kazdego x typu 'a,
  jezeli P(MyList xs) to P(MyList x xs)
*)

type ('a, 'b) hihi = 
  | C1 of 'a
  | C2 of 'b * ('a, 'b) hihi  
  | C3 of ('a, 'b) hihi * ('a, 'b) hihi * ('a, 'b) hihi
  | C4

(* 
* dla kazdego x typu 'a, P(C1 x) ^
* dla kazdego y typu 'b, dla kazdego d typu 'a 'b hihi, P(d) -> P( C2(b, d) ) ^
* dla kazdego d, e, f typu 'a 'b hihi, (P(d) ^ P(e) ^ P(f)) -> P(C3(d, e, f)) ^
* (P(C4)) --> dla kazdego d od hihi P(d)
*)

type 'a tree = 
  | Leaf 
  | Node of 'a tree * 'a * 'a tree

(* 
Zasada indukcji: dla każdej własności P,
* jeśli P(Leaf)
* oraz dla każdego (a : 'a) i l, r : 'a tree, P(l) i P(r) implikuje P(Node (l, a, r))
* to dla każdego drzewa t typu 'a tree zachodzi P(t) 
*)


(* ----------------------- ZAD5 - napisz funkcje ktora buduje 
                       kompletne drzewo bst z posortowanej listy *)

(* Zwraca parę: zbudowane drzewo i reszta listy nieprzetworzona *)
let rec build_tree n lst =
  if n = 0 then
    (Leaf, lst)
  else
    let left_size = n / 2 in
    let right_size = n - left_size - 1 in
    let (left_tree, lst1) = build_tree left_size lst in
    match lst1 with
    | [] -> failwith "Unexpected empty list"
    | x::xs ->
      let (right_tree, rest) = build_tree right_size xs in
      (Node (left_tree, x, right_tree), rest);;

let sorted_list_to_tree lst =
  let len = List.length lst in
  let (tree, _) = build_tree len lst in
  tree;;
