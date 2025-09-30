open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

let rec subst (x : ident) (s : expr) (e : expr) : expr =
  match e with
  | Binop (op, e1, e2) -> Binop (op, subst x s e1, subst x s e2)
  | If (b, t, e) -> If (subst x s b, subst x s t, subst x s e)
  | Var y -> if x = y then s else e
  | Let (y, e1, e2) ->
      Let (y, subst x s e1, if x = y then e2 else subst x s e2)
  | _ -> e

let reify (v : value) : expr =
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b

let rec eval (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval e1) (eval e2)
  | If (b, t, e) ->
      (match eval b with
           | VBool true -> eval t
           | VBool false -> eval e
           | _ -> failwith "type error")
  | Let (x, e1, e2) ->
      eval (subst x (reify (eval e1)) e2)
  | Var x -> failwith ("unknown var " ^ x)

module M = Map.Make(String)
type env = value M.t

let rename_expr (e : expr) : expr =
  let rec rename e path env =
    match e with 
    | Int j -> Int j
    | Bool b -> Bool b
    
    | Binop(op, e1, e2) -> 
      Binop(op, rename e1 (path ^ "L") env,
                rename e2 (path ^ "R") env)

    | If(c, t, e) ->
      If(rename c (path ^ "C") env,
         rename t (path ^ "T") env,
         rename e (path ^ "E") env)
    
    | Let(x, e1, e2) ->
      let fresh_var = "#" ^ path in
      Let(fresh_var,
          rename e1 (path ^ "L") env,
          rename e2 (path ^ "R") (M.add x fresh_var env)) 

    | Var x -> 
      (match M.find_opt x env with 
      | None -> Var x
      | Some y -> Var y)
         
  in rename e "" M.empty 

let test = rename_expr (
  Let ("x", Int 1,
    Binop (Add,
      Let ("y", Int 2,
        Binop (Add, Binop (Add, Var "x", Var "y"), Var "z")),
      Let ("x", Var "x", Var "x")
    )
  )
);;

let interp (s : string) : value =
  eval (parse s)
