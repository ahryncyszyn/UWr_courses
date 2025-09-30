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

(*------------------------------- INTERPRETER EXPLICIT -------------------------------*)
(* EXPLICIT - z jawnie przekazywanym stanem (sterta) *)
(* zamiast korzystać z globalnej, niewidocznej pamięci, 
   stan (sterta) jest przekazywany jako parametr do eval *)

(* sterta to mapa ktora przechowuje (int -> value), gdzie klucz jest adresem *)
module Loc = Int
module H = Map.Make(Loc)

module M = Map.Make(String)
type env = value M.t
and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env
  | VRef of Loc.t

type heap = value H.t
(* funkcja ktora generuje nowy adres w stercie *)
(* doslownie to zwraca liczbe aktualnych elementow sterty *)
let fresh h = H.cardinal h

let int_op op v1 v2 h =
  match v1, v2 with
  | VInt x, VInt y -> (VInt (op x y), h)
  | _ -> failwith "type error"

let cmp_op op v1 v2 h =
  match v1, v2 with
  | VInt x, VInt y -> (VBool (op x y), h)
  | _ -> failwith "type error"

let bool_op op v1 v2 h =
  match v1, v2 with
  | VBool x, VBool y -> (VBool (op x y), h)
  | _ -> failwith "type error"

(* zamiast zwracac tylko value zwraca pare (value, heap) *)
let eval_op (op : bop) : value -> value -> heap -> value * heap =
  match op with
  | Add  -> int_op ( + )
  | Sub  -> int_op ( - )
  (* ... *)
  | Eq   -> (fun v1 v2 h -> (VBool (v1 = v2), h))
  | Neq  -> (fun v1 v2 h -> (VBool (v1 <> v2), h))
  | Assgn -> (fun v1 v2 h ->
      match v1 with
      | VRef r -> (VUnit, H.add r v2 h)
      | _ -> failwith "type error")
  | _ -> failwith("todo");;

let rec eval_env (env : env) (e : expr) (h : heap) : value * heap =
  match e with
  | Int i -> (VInt i, h)
  | Bool b -> (VBool b, h)
  | Binop (op, e1, e2) ->
      let (v1, h) = eval_env env e1 h in
      let (v2, h) = eval_env env e2 h in
      eval_op op v1 v2 h
  | If (b, t, e) ->
      let (v, h) = eval_env env b h in
      (match v with
      | VBool true -> eval_env env t h
      | VBool false -> eval_env env e h
      | _ -> failwith "type error")
  | Var x ->
      let v =
        match M.find_opt x env with
        | Some v -> v
        | None -> failwith "unknown var"
      in (v, h)
  (* ... *)
  | Fun (x, e) -> (VClosure (x, e, env), h)
  | Funrec (f, x, e) -> (VRecClosure (f, x, e, env), h)
  | App (e1, e2) ->
      let (v1, h) = eval_env env e1 h in
      let (v2, h) = eval_env env e2 h in
      (match v1 with
        | VClosure (x, body, clo_env) ->
            eval_env (M.add x v2 clo_env) body h
        | VRecClosure (f, x, body, clo_env) as c ->
            eval_env (clo_env |> M.add x v2 |> M.add f c) body h
        | _ -> failwith "not a function")
  | Ref e ->
      let (v, h) = eval_env env e h in
      (* generowanie nowego adresu r *)
      let r = fresh h in
      (* zwracamy referencje na adres r *)
      (* i zapisujemy wartosc v pod adresem r w mapie h *)
      (VRef r, H.add r v h)
  | Deref e ->
      let (v, h) = eval_env env e h in
      (match v with
        (* odczytujemy wartosc pod adresem r w stercie *)
        | VRef r -> (H.find r h, h)
        | _ -> failwith "not a reference")
  | _ -> failwith("todo")

let eval e = fst (eval_env M.empty e H.empty)


