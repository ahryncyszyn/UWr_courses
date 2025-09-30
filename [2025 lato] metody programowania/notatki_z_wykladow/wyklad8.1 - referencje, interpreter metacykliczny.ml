(*------------------------------- MUTOWALNOSC -------------------------------*)
(* w czysto funkcyjnym jezyku nie istnieje mutowalnosc *)
(* tutaj ja implementujemy uzywajac referencji *)
let x = ref 42;; (* tworzy wskaznik do 42, val x : int ref = {contents = 42} *)
x := !x + 1;;    (* zmiana wartosci pod x *)
!x;;             (* dereferencja, x : 43 *)

(*------------------------------- TYPY -------------------------------*)
type bop =                                                     (* AST *)
  | Add | Sub | Mult | Div | And | Eq | Neq
  | Assgn   (* assignment (:= ) *)
type ident = string

type expr = 
  | Int    of int
  | Bool   of bool
  | Binop  of bop * expr * expr
  | If     of expr * expr * expr
  | Let    of ident * expr * expr
  | Var    of ident
  | Unit
  | Pair   of expr * expr
  | Fst    of expr
  | Snd    of expr
  | Match  of expr * ident * ident * expr
  | IsPair of expr
  | Fun    of ident * expr
  | Funrec of ident * ident * expr
  | App    of expr * expr
  | Ref    of expr
  | Deref  of expr

module M = Map.Make(String)
type env = value M.t
and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env
  (* musi byc value ref bo typ ref to 'a ref *)
  | VRef of value ref        (* referencja *)

(*------------------------------- INTERPRETER METACYKLICZNY -------------------------------*)
(* interpreter napisany w tym samym języku, który interpretuje *)
(* np uzywamy ref z Ocamla zeby ewaluowac referencje w naszym jezyku *)
let int_op op v1 v2 =
  match v1, v2 with
  | VInt x, VInt y -> VInt (op x y)
  | _ -> failwith "type error"

let cmp_op op v1 v2 =
  match v1, v2 with
  | VInt x, VInt y -> VBool (op x y)
  | _ -> failwith "type error"

let bool_op op v1 v2 =
  match v1, v2 with
  | VBool x, VBool y -> VBool (op x y)
  | _ -> failwith "type error"

(* zwraca funkcje uzywana w eval_env zamiast od razu wyliczyc wartosc *)
let eval_op (op : bop) : value -> value -> value =
  match op with
  | Add  -> int_op ( + )
  | And  -> bool_op ( && )
  (* ... *)
  (* zwraca funkcje ktora wykonuje (v1 := v2) i zwraca typ VUnit *)
  (* musimy zapewnic ze v1 jest referencja (VRef) *)
  | Assgn -> (fun v1 v2 ->
      match v1 with
      | VRef r -> r := v2; VUnit
      | _ -> failwith "type error")
  | _ -> failwith("todo");;

let rec eval_env (env : env) (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      let v1 = eval_env env e1 in
      let v2 = eval_env env e2 in
      eval_op op v1 v2
  (* ... *)
  (* uzywa ocamlowego "ref" zeby stworzyc referencje *)
  | Ref e ->
      let v = eval_env env e in
      VRef (ref v)
  (* uzywa ocamlowego "!" zeby zaaplikowac dereferencje *)
  | Deref e ->
      let v = eval_env env e in
      (match v with
        | VRef r -> !r
        | _ -> failwith "not a reference")
  | _ -> failwith("todo")

let eval = eval_env M.empty
