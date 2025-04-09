(* Gramatykę w postaci BNF można reprezentować w OCamlu przy użyciu następującego typu: *)

type 'a symbol =
| T of string (* symbol terminalny *)
| N of 'a (* symbol nieterminalny *)

(* gramatyka to lista krotek: (symbol_nieterminalny, lista rozwiniec/produkcji) *)
type 'a grammar = ('a * ('a symbol list) list ) list;;

(* Zaimplementuj funkcję która generuje słowo należące do języka poprzez rozwijanie 
   symbolu nieterminalnego przy użyciu produkcji wybranej w sposób pseudolosowy. *)
(* Do rozwiązania mogą przydać się następujące funkcje:
Random.int : int -> int – losowa liczba z zakresu 0..n-1
List.length : 'a list -> int – długość listy
List.assoc : 'a -> ('a * 'b ) list -> 'b – wyszukanie elementu na liście asocjacyjnej
String.concat : string -> string list -> string – konkatenacja listy stringów z separatorem *)
(* generate : 'a grammar -> 'a -> string *)

let rec nth xs n =
  match xs with
  | [] -> failwith "lista krotsza niz n"
  | x::xs' -> if n = 0 then x else nth xs' (n-1);;


let rec generate gram s =
  let options = List.assoc s gram in
  let max_num = List.length options in
  let num = Random.int max_num in 
  let words = nth options num in
  String.concat " " (List.map (fun x -> match x with
                                        | T str -> str 
                                        | N x -> generate gram x) words);;


let pol : string grammar =
  [ "zdanie", [[ N "grupa - podmiotu "; N "grupa - orzeczenia "]]
  ; "grupa - podmiotu ", [[ N "przydawka"; N "podmiot"]]
  ; "grupa - orzeczenia ", [[ N "orzeczenie"; N "dopelnienie"]]
  ; "przydawka", [[ T "Piekny"]; [ T "Bogaty"]; [ T "Wesoly"]]
  ; "podmiot", [[ T "policjant"]; [ T "student"]; [ T "piekarz"]]
  ; "orzeczenie", [[ T "zjadl"]; [ T "pokochal"]; [ T "zobaczyl"]]
  ; "dopelnienie", [[ T "zupe."]; [ T "sam siebie."]; [ T "instytut informatyki."]]];;

let expr : unit grammar =
  [() , [[ N () ; T "+"; N () ];
  [ N () ; T "*"; N () ];
  [ T "("; N () ; T ")"];
  [ T "n" ]]]