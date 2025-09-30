open RawAst

exception Type_error of
  (Lexing.position * Lexing.position) * string

module Env = struct
  module StrMap = Map.Make(String)
  type t = typ StrMap.t

  let initial = StrMap.empty

  let add_var env x tp =
    StrMap.add x tp env

  let lookup_var env x =
    StrMap.find_opt x env
end

type type_error = 
{
  loc : Lexing.position * Lexing.position;
  msg : string;
}

let add_error loc msg errors =
  { loc; msg } :: errors
  
let rec infer_type env (e : expr) : typ * type_error list =
  match e.data with
  | Unit   -> (TUnit, [])
  | Int  _ -> (TInt, [])
  | Bool _ -> (TBool, [])
  | Var  x ->
    begin match Env.lookup_var env x with
    | Some tp -> (tp, [])
    | None    ->
      (TUnit, [ { loc = e.pos; msg = Printf.sprintf "unbound variable %s" x } ])
    end
  | Binop((Add | Sub | Mult | Div), e1, e2) ->
    let (t1, errors1) = infer_type env e1 in
    let (t2, errors2) = infer_type env e2 in
    let errs = ref (errors1 @ errors2) in
    if t1 <> TInt then errs := add_error e1.pos "left operand must be int" !errs;
    if t2 <> TInt then errs := add_error e2.pos "right operand must be int" !errs;
    (TInt, !errs)
  | Binop((And | Or), e1, e2) ->
    let (t1, errs1) = infer_type env e1 in
    let (t2, errs2) = infer_type env e2 in
    let errs = ref (errs1 @ errs2) in
    if t1 <> TBool then errs := add_error e1.pos "left operand must be bool" !errs;
    if t2 <> TBool then errs := add_error e2.pos "right operand must be bool" !errs;
    (TBool, !errs)
  | Binop((Leq | Lt | Geq | Gt), e1, e2) ->
    let (t1, errs1) = infer_type env e1 in
    let (t2, errs2) = infer_type env e2 in
    let errs = ref (errs1 @ errs2) in
    if t1 <> TInt then errs := add_error e1.pos "left operand must be int" !errs;
    if t2 <> TInt then errs := add_error e2.pos "right operand must be int" !errs;
    (TBool, !errs)
  | Binop((Eq | Neq), e1, e2) ->
    let (t1, errs1) = infer_type env e1 in
    let (t2, errs2) = infer_type env e2 in
    let errs = ref (errs1 @ errs2) in
    if t1 <> t2 then errs := add_error e1.pos "operands must be of the same type" !errs;
    (TBool, !errs)
  | If(b, e1, e2) ->
    let (tb, errb) = infer_type env b in
    let (t1, err1) = infer_type env e1 in
    let (t2, err2) = infer_type env e2 in
    let errs = ref (errb @ err1 @ err2) in
    if tb <> TBool then errs := add_error b.pos "condition must be bool" !errs;
    if t1 <> t2 then errs := add_error e1.pos "branches must have the same type" !errs;
    (t1, !errs)
  | Let(x, e1, e2) ->
    let (t1, err1) = infer_type env e1 in
    let (t2, err2) = infer_type (Env.add_var env x t1) e2 in
    (t2, err1 @ err2)
  | Pair(e1, e2) ->
    let (t1, err1) = infer_type env e1 in
    let (t2, err2) = infer_type env e2 in
    (TPair(t1, t2), err1 @ err2)
  | App(e1, e2) ->
    let (t_fun, err1) = infer_type env e1 in
    let (t_arg, err2) = infer_type env e2 in
    let errs = ref (err1 @ err2) in
    begin match t_fun with
    | TArrow(t_expected, t_ret) ->
        if t_expected <> t_arg then
          errs := add_error e2.pos "argument type mismatch in application" !errs;
        (t_ret, !errs)
    | _ ->
        errs := add_error e1.pos "trying to apply a non-function" !errs;
        (TUnit, !errs)
    end
  | Fst e ->
    let (tp, errs) = infer_type env e in
    begin match tp with
    | TPair(t1, _) -> (t1, errs)
    | _ -> (TUnit, add_error e.pos "fst expects a pair" errs)
    end
  | Snd e ->
    let (tp, errs) = infer_type env e in
    begin match tp with
    | TPair(_, t2) -> (t2, errs)
    | _ -> (TUnit, add_error e.pos "snd expects a pair" errs)
    end
  | Fun(x, t_arg, body) ->
    let (t_ret, errs) = infer_type (Env.add_var env x t_arg) body in
    (TArrow(t_arg, t_ret), errs)
  | Funrec(f, x, t_arg, t_ret, body) ->
    let env1 = Env.add_var env f (TArrow(t_arg, t_ret)) in
    let env2 = Env.add_var env1 x t_arg in
    let (t_body, errs) = infer_type env2 body in
    let errs =
      if t_body <> t_ret then add_error body.pos "function body does not match declared return type" errs
      else errs
    in
    (TArrow(t_arg, t_ret), errs)

and check_type env e tp =
  let tp' = infer_type env e in
  if tp = tp' then ()
  else raise (Type_error(e.pos,
  Printf.sprintf "wrong type"))

let check_program e =
  let (_tp, errs) = infer_type Env.initial e in
  List.iter (fun {loc = (start_pos, end_pos); msg} ->
    Printf.printf "Error from %d to %d: %s\n"
      start_pos.Lexing.pos_cnum end_pos.Lexing.pos_cnum msg
  ) errs

(* 
open Fun.TypeCheck;;
open Fun.RawAst;;
let bad_expr = node (Binop(Eq, node (Int 1), node (Bool true)));;
let bad_expr = node (Fst (node (Pair (node (Bool true), node (Int 2)))));;
let bad_expr = node (Fst (node (Int 2)));;
let bad_expr = node (Let ("x",
    node (Binop(Eq, node (Int 1), node (Bool true))),  
    node (Fst (node (Int 2)))));;
check_program bad_expr;;
*)