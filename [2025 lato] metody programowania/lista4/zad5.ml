
(* Używając sygnatury słownika KDICT, zaimplementuj funkcję freq w funktorze Freq *)
(* Wartością zwracaną powinna być lista par, których pierwszym elementem są elementy listy wejściowej xs, a drugim – liczba wystąpień tego elementu w tej liście. *)

module Freq (D : KDICT) = struct
  let freq xs =
    let rem cout_elements lst dict =  
      match list with 
      | [] -> dict
      | x :: xs' -> 
        let curr_count = match D.find_opt z dict with
        | Some c -> c + 1
 	| None -> 1
	in count_elements xs' (D.insert x curr_count);;

: D.key list) : (D.key * int) list =
  
end


(* Wykorzystując funktor Freq, napisz funkcję char_freq, obliczającą 
liczbę wystąpień znaków w ciągu typu string *)

let list_of_string s = String.to_seq s |> List.of_seq
