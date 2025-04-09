
(* Utwórz otypowany analogicznie do funktora MakeListDict z zadania 3 funktor MakeMapDict, wykorzystujący wbudowane w bibliotekę standardową OCamla słowniki z modułu Map. Następnie, korzystając z napisanego funktora, utwórz moduł CharMapDict. Pamiętaj o użyciu with type.
 *)

module type KDICT = sig
  type key
  type 'a dict
  val empty : 'a dict
  val insert : key -> 'a -> 'a dict -> 'a dict
  val remove : key -> 'a dict -> 'a dict
  val find_opt : key -> 'a dict -> 'a option
  val find : key -> 'a dict -> 'a
  val to_list : 'a dict -> (key * 'a) list
end;;

module MakeMapDict (Ord : Map.OrderedType) : KDICT with type key = Ord.t = struct
  module M = Map.Make(Ord)
  type key = Ord.t
  type 'a dict = 'a M.t
  let empty = M.empty
  let insert key value dict = M.add key value dict
  let remove key dict = M.remove key dict
  let find_opt key dict = M.find_opt key dict
  let find key dict = match find_opt key dict with | Some v -> v | None -> failwith "Key not found"
  let to_list dict = M.bindings dict
end;;

module CharMapDict = MakeMapDict(Char);;

let d = CharMapDict.insert 'a' 1 CharMapDict.empty;;
let d = CharMapDict.insert 'b' 2 d;;
let d = CharMapDict.insert 'c' 3 d;;

CharMapDict.find 'a' d;;
CharMapDict.find 'b' d;;
CharMapDict.find 'c' d;;

let d = CharMapDict.remove 'b' d;;

CharMapDict.find_opt 'b' d;;

CharMapDict.to_list d;;


