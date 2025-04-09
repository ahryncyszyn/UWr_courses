(* zad 2 - zdefiniuj dwuargumentową funkcję compose, której 
wynikiem jest złożenie (jednoargumentowych) funkcji przekazanych
jej jako argumenty *)

let compose f g x = f (g x);;

let square x = x * x;;
let inc x = x + 1;;
compose square inc 5;;
(* --> square (inc 5) --> square (6) --> 36 *)
compose inc square 5;;
(* --> inc (square 5) --> inc (25) --> 26 *)