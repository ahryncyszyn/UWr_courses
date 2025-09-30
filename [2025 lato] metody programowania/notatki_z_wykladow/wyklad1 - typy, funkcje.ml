

(*------------------------------- TYPY -------------------------------*)
(* int ma 31 bitow a nie 32! jeden uzywany przez garbage collector *)
let a = 2;;
let b = a + 1;;

(* wartosci boolowskie *)
a = b;; (* ==, porownanie strukturalne *)
a <> b;; (* != *)

(* zamiana typow musi byc jawna *)
(* nie ma instrukcji, tylko wyrazenia! kazde ma konkretny typ *)
if a = b then 1 else 0;;

(* float zapisujemy z kropka, nawet gdy mmay tylko czesc calkowita!! *)
(* inny operator dodawania! wszystko tez z kropka poza = *)
2.5 +. 3.;;

(* konwersja typow - wbudowane funkcje *)
float_of_string "1";;

(* exceptions *)
failwith "błąd"

(* stringi *)
let _ = String.make 2 'a';; (* "aa" *)
"foo" ^ "bar";; (* "foobar" *)
"foo".[0];; (* 'f' *)
String.length "foo";; (* 3 *)
print_string "abc";; (* printuje i zwraca typ unit *)

(* unit - ma tylko jedna wartosc, krotka z 0 elementami skladowymi *)
(* jest typem zwracanym przez fukcje analogiczne do void *)
();;

(*------------------------------- FUNKCJE -------------------------------*)
let increment x = x + 1;;
increment;; (* int -> int = <fun> *)
increment 1;; (* 2 *)

let square x = x *. x;;
square 2.;; (* 4 *)
square (square 2.);; (* 16 *)

(* 
val compose : ('b -> 'c) -> ('a -> 'b) -> 'a -> 'c 
bo g: ('a -> 'b), wiec (g x): 'b 
a f: ('b -> 'c), wiec funkcja zwraca typ 'c *)
let compose f g x = f(g(x));;
compose square square 2.;; (* 16 *)

let add1float x = (+.) 1.;;
add1float 2.;; (* 3 *)

(* let in pozwala na lokalne definiowanie zmiennych *)
2 + (let (+) = ( * ) in 3 + 5) (* 2 + 3 * 15 = 17 *)

(* and pozwala na rownoczesne definiowanie*)
let a = 4;;
let a = 5 and b = a + 2 in a * b;; (* 30, bo uzywa poprzedniej wersji a!! *)
let a = a + 1 in a;; (* 5 *)

(* funkcje anonimowe *)
fun x -> x + 1;;

(* tozsame *)
let inc x = x + 1
let inc = fun x -> x + 1
