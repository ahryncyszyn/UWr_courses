(* zad 1 - iloczyn elementow listy uzywajac fold left *)

let fold_left f a xs =
  let rec it xs acc =
    match xs with
    | [] -> acc
    | x::xs -> it xs (f acc x)
  in it xs a;;

let product xs = fold_left ( * ) 1 xs;;
(* zwraca 1 dla pustej listy *)
(* jest to element neutralny bo 1 * x = x *)
(* gdybysmy uzyli 0 to zawsze byłoby zwracane 0 *)