
(* Zamień definicję ListDict z zadania 1 na definicję funktora MakeListDict, 
sparametryzowanego modułem o sygnaturze Map.OrderedType, i zwracającego 
moduł o sygnaturze KDICT z zadania 2. *)

(* Następnie, korzystając z napisanego funktora, utwórz moduł CharListDict. *)

module type KDICT = sig
  type key
  type 'a dict
  val empty : 'a dict
  val insert : key -> 'a -> 'a dict -> 'a dict 
  val remove : key -> 'a dict -> 'a dict
  val find_opt : key -> 'a dict -> 'a option
  val find : key -> 'a dict -> 'a
  val to_list : 'a dict -> (key * a') list
end

Module MakeListDict (Ord : Map.OrderedType) :
  (KDICT with type key = Ord.t) = struct

  type key = Ord.t

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
    | (k, v) :: t -> if Ord.compare k key then v
	                    else find key t

  let to_list dict = dict
end;;
  

Module CharListDict = MakeListDict (struct
  Type t = int * int
  Let compare (x, _) (y, _) = 

