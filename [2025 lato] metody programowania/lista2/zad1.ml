
(* zad1 - dwie implementacje obliczania ciagu fibonacciego *)

let rec fib n =
  if n = 0 then 0
  else if n = 1 then 1
  else fib (n-1) + fib (n-2);;

(* nazywa sie iteracyjna bo rekursja ogonowa wykonuje sie O(n) razy *)
(* a = fib(n-2), b = fib(n-1) *)
let rec fib_iter n = 
  let rec fib_hlp n a b = 
    if n = 0 then a
    else if n = 1 then b
    else fib_hlp (n - 1) b (a + b)
  in fib_hlp n 0 1;;

(* normalna rekursja fib 50 - czas to ponad minuta - złozonośc O(2^n) *)
(* rekursja ogonowa fib_iter 50 - czas to jakas sekunda  - złozonośc O(n) *)