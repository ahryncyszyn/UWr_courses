
(* Rozbuduj funkcję parens_ok z poprzedniego zadania tak, by sprawdzała poprawne
nawiasowania składające się z symboli ’(’, ’)’, ’[’, ’]’, ’{’ oraz ’}’. *)

let parens_ok str =
  let rec check xs stack =
  match xs with 
  | [] -> if stack = [] then true else false
  | '('::xs' -> check xs' ('('::stack)
  | '{'::xs' -> check xs' ('{'::stack)
  | '['::xs' -> check xs' ('['::stack)
  | ')'::xs' -> if stack = [] || List.hd stack <> '(' then false else check xs' (List.tl stack)
  | '}'::xs' -> if stack = [] || List.hd stack <> '{' then false else check xs' (List.tl stack)
  | ']'::xs' -> if stack = [] || List.hd stack <> '[' then false else check xs' (List.tl stack)
  | _::_ -> false
  in check (List.of_seq (String.to_seq str)) [];;