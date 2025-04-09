
(* Zaimplementuj funkcję parens_ok : string -> bool, ktora
   sprawdza, czy argument jest napisem zawierającym tylko symbole ’(’ oraz
   ’)’, które tworzą poprawne nawiasowanie. *)

let parens_ok str =
  let rec check xs opened =
  match xs with 
  | [] -> if opened = 0 then true else false
  | '('::xs' -> check xs' (opened + 1)
  | ')'::xs' -> if opened = 0 then false else check xs' (opened - 1)
  | _::_ -> false
  in check (List.of_seq (String.to_seq str)) 0;;


