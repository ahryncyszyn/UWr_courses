
(* moduł Map implementuje słownik używając drzewa zrównoważonego *)

(* zamiast zwykłych operatorów < i =, porządek jest definiowany następującą sygnaturą: *)

module type OrderedType = sig 
  type t
  val compare : t -> t -> int 
end

(* zwraca -1 gdy pierwszy element jest mniejszy, 0 gdy równy, 1 gdy większy od drugiego *)

(* zmodyfikować DICT tak, żeby typ kluczy był ustalonym (choć nieznanym) typem zamiast parametrem typowym typu dict *)

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

