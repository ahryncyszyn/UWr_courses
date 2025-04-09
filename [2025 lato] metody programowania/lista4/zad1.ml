
(* zaimplementuj słownik przy użyciu list par kluczy i wartości *)

module type DICT = sig
  type ('a, 'b) dict
  val empty : ('a, 'b) dict
  val insert : 'a -> 'b -> ('a, 'b) dict -> ('a, 'b) dict 
  val remove : 'a -> ('a, 'b) dict -> ('a, 'b) dict
  val find_opt : 'a -> ('a, 'b) dict -> 'b option
  val find : 'a -> ('a, 'b) dict -> 'b
  val to_list : ('a, 'b) dict -> ('a * 'b) list
end;;

module ListDict : DICT = struct
  type ('a, 'b) dict = ('a * 'b) list

  let empty = []

  let insert key value dict = (key, value) :: remove k d

  let remove key dict = List.filter (fun (k, _) -> key <> k) dict

  let rec find_opt key dict =
    match dict with
    | [] -> None
    | (k, v) :: t -> if k = key then Some v
                    else find_opt key t

  let rec find key dict = 
    match dict with
    | [] -> failwith "key not found"
    | (k, v) :: t -> if k = key then v
	                    else find key t

  let to_list dict = dict
end;;


(* testowanie *)
let d0 = ListDict.empty;;
d0 = ListDict.insert 1 "hihi" d0;;
let l0 = ListDict.to_list d0;;

let d0 = ListDict.insert 2 "hehe" d0;;
let a = ListDict.find 2 d0;; 


let d0 = ListDict.remove 2 d0;;  
let a = ListDict.find_opt 2 d0;; 



  
    
