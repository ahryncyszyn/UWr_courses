
(* zad 8 - sortowanie przez wybor *)

(* zwraca najmniejszy element listy *)
let rec find_min lst min_num = 
  match lst with 
  | [] -> min_num
  | h :: t -> find_min t (min h min_num);;

(* zwraca pare składajaca sie z najmniejszego elementu i reszty listy *)
let rec select lst = 
  match lst with
  | [] -> failwith "pusta lista nie ma minimum"
  | [x] -> (x, [])
  | h :: t -> 
    let min_num = find_min t h in 
    let rec remove_min lst = 
      match lst with
      | [] -> []
      | h :: t when h = min_num -> t
      | h :: t -> h :: remove_min t
    in (min_num, remove_min lst);;

let rec select lst = 
  match lst with
  | [] -> failwith "pusta lista nie ma minimum"
  | [x] -> (x, [])
  | h :: t -> let (min_val, rest) = select t in
              if (h < min_val) then (h, t)
              else (min_val, h::rest);;

(* sortowanie przez wybor *)
let rec select_sort lst = 
  match lst with
  | [] -> []
  | _ -> 
    let (min_num, rest) = select lst in
    min_num :: select_sort rest;;