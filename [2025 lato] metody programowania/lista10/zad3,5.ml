type ident = string

type bop =
  (* arithmetic *)
  | Add | Sub | Mult | Div
  (* logic *)
  | And | Or
  (* comparison *)
  | Eq | Neq | Leq | Lt | Geq | Gt


type cmd =
  | PushInt  of int
  | PushBool of bool
  | PushPair
  | PushUnit
  | Fst
  | Snd
  | IsPair
  | Binop    of bop
  | CndJmp   of prog * prog
  | PushVar of ident       (* zad 5 *)

and prog = cmd list

let rec stack_size (p : prog) : int =
  let rec aux cmds current max_seen bools =
    match cmds with
    | [] -> max_seen
    | cmd :: rest ->
        let delta, bools' =
          match cmd, bools with
          | PushVar _, _ -> (1, bools)              (* zad 5 *)
          | PushBool b, _ -> (1, (b :: bools)) 
          | PushInt _, _ | PushUnit, _ -> (1, bools)
          | Binop _, _ | PushPair, _ -> (-1, bools)
          | Fst, _ | Snd, _ | IsPair, _ -> (0, bools)
          | CndJmp (t, e), true :: rest -> ((stack_size t) - 1, rest)
          | CndJmp (t, e), false :: rest -> ((stack_size e) - 1, rest)
          | CndJmp (_, _), [] -> failwith ("brakuje boola")
        in let new_current = current + delta
        in let new_max = max max_seen new_current
        in aux rest new_current new_max bools'
    in aux p 0 0 []

let test2 = [
  PushBool true;
  PushInt 3;
  PushInt 5;
  CndJmp ([Binop Add], [Binop Sub])
];;

let test4 = [
  PushInt 3;
  PushInt 5;
  PushPair;
  Fst;
  PushInt 2;
  PushBool false;
  CndJmp ([Binop Add], [Binop Sub])
];;

let test_logic = [
  PushBool true;
  PushBool false;
  Binop And
];;

let test_cond_true = [
  PushBool true;
  CndJmp ([PushInt 1; PushInt 2; Binop Add], [PushInt 0])
];;

let test_var = [
  PushVar "x";
  PushInt 2;
  Binop Add
];;

let test_empty = [];;


