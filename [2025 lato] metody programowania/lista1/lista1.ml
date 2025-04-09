
(* zad 1 - jaki wynik? *)
10;; (* int = 10 *)
2 * 3 + 4;; (* 10 *)
2 * (3 + 4);; (* 14 *)
let a = 3;; (* val a : int = 3 *)
let b = a + 1;; (* val b : int = 4 *)
if b > a && b < a * b then b else a;; (* int = 4 *)
2 + (if b > a then b else a);; (* int = 6 *)
let a = if b * b > b then b else -1 in a * b;; (* int = 16, bo 4 * 4 *)

(* zad 2 - czy jest poprawnie otypowane? *)
"foo" ^ 42; (* nie - string i int *)
"foo" ^ string_of_int 42;; (* "foo42" *)
1. = 2;; (* nie - float i int *)
fun a -> a + 5;; (* int -> int = <fun> *)
fun a -> if a > 5 then a else " foo";; (* nie - zwraca int i string *)
fun a b -> if a > 5 then a else b ;; (* int -> int -> int = <fun> *)

fun a b ->
  let c = a = b in
  if a > 3 && b = " foo"
  then c
  else false ;; (* nie - b powinno byc int a nie string *)

fun a ->
  let f a b = a * a + b * b in
  f ( f a a ) a ;; (* int -> int = <fun> *)

let f a = a > 2 in
  if 3 > 2 then true else f ( f 2) ;; (* nie - powinien byc int a nie bool *)

(* zad 3 - wolne i zwiazane wystapienia zmiennych *)
x ;; (* wolna zmienna, chyba ze zostala zadeklarowana wczesniej *)
let x = 3 in x + y ;; (* unbound *)
let x = 1 and y = x + 2 in x + y ;; (* unbound bo definiowane rownoczesnie *)
let x = 1 in let y = x + 2 in x + y ;; (* lokalne zdefiniowanie *)
let f x y = x * y * z ;; (* unbound *)
let f x = let g y z = x * y * z in g ( h x ) z ;; (* unbound h *)

(* zad 4 - zdefniuj funkcję o trzech argumentach będących liczbami całkowitymi, której
wynikiem jest suma kwadratów dwóch większych jej argumentów *)
fun min a b -> if a < b then a else b;;
let sum_of_squares_of_largest a b c ==
  let smallest = min a (min b c) in
  (a * a + b * b + c * c) - (smallest * smallest);;

(* zad 5 *)
let a_plus_abs_b a b =
  (if b > 0 then (+) else (-) ) a b;;

(* zad 6 *)
(* gorliwe obliczanie - najpierw oblicza wszystkie argumenty *)
(* leniwe obliczanie - argumenty obliczane dopiero gdy sa potrzebne *)

let rec f () = f ();;
let test x y = if x = 0 then 0 else y;;
test 0 (f ());; (* powoduje zawieszenie czyli uzywa gorliwej strategii *)