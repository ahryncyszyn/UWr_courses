
(* zad 3 - zaimplementuj funkcję build_list n f, która konstruuje
n-elementową listę aplikując f do wartości od 0 do n − 1 *)

let build_list n f = 
  let rec build i acc =
    if i < 0 then acc
    else build (i - 1) (f i :: acc)
  in build (n - 1) [];;

  
(* napisz nastepujace funkcje: *)
(* negatives n, zwracającą listę liczb ujemnych od −1 do −n, *)
let negatives n = build_list n (fun x -> - (x + 1));;

(* reciprocals n, zwracającą listę odwrotności liczb od 1 do n *)
let reciprocals n = build_list n (fun x -> 1. /. float_of_int (x + 1));;

(* evens n, zwracajacą listę pierwszych n liczb parzystych *)
let evens n = build_list n (fun x -> 2 * x);;

(* identityM n, zwracającą macierz identycznościową o wymiarach n × n w
postaci listy list *)
let identityM n =
  build_list n (fun x -> 
    build_list n (fun y -> if x = y then 1 else 0));;
