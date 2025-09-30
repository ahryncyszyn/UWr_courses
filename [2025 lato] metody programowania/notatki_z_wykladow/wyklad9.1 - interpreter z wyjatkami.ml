(*------------------------------- TYPY -------------------------------*)
type bop =                                                     (* AST *)
  | Add | Sub | Mult | Div | And | Eq | Neq | Gt
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
  | Match  of expr * ident * ident * expr
  | IsPair of expr
  | Fun    of ident * expr
  | Funrec of ident * ident * expr
  | App    of expr * expr
  | Try    of expr * expr             (* try e1 with e2 *)
  | Throw

(*------------------------------- INTERPRETER MONADYCZNY Z WYJATKAMI -------------------------------*)
(* - wykorzystujemy monade opcji ('a comp = 'a option) jako reprezentację możliwego zawieszenia obliczenia *)
(* - typ 'a option zawiera albo wartośc Some 'a dla wyniku albo None dla bledu *)

module M = Map.Make(String)
type env = value M.t
and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env

type 'a comp = 'a option

let return (v : 'a) : 'a comp =
  Some v

let bind (c : 'a comp) (f : 'a -> 'b comp) : 'b comp =
  match c with
  | Some v -> f v
  | None -> None         (* wyjątek propaguje się dalej *)

let (let* ) = bind

let int_op op v1 v2 =
  match v1, v2 with
  | VInt x, VInt y -> Some (VInt (op x y))
  | _ -> failwith "type error"

let cmp_op op v1 v2 =
  match v1, v2 with
  | VInt x, VInt y -> Some (VBool (op x y))
  | _ -> failwith "type error"

let bool_op op v1 v2 =
  match v1, v2 with
  | VBool x, VBool y -> Some (VBool (op x y))
  | _ -> failwith "type error"

let eval_op (op : bop) : value -> value -> value comp =
  match op with
  | Add  -> int_op ( + )
  | Sub  -> int_op ( - )
  | Eq   -> fun v1 v2 -> Some (VBool (v1 = v2))
  | Neq  -> fun v1 v2 -> Some (VBool (v1 <> v2))
  | Gt   -> cmp_op ( > )
  | _ -> failwith("todo")

let rec eval_env (env : env) (e : expr) : value comp =
  match e with
  | Int i -> return (VInt i)
  | Bool b -> return (VBool b)
 (* ewaluacja tak samo jak w intepreterze monadycznym *)
 (* ... *)
  | Fun (x, e) -> return (VClosure (x, e, env))
  | Funrec (f, x, e) -> return (VRecClosure (f, x, e, env))
  | App (e1, e2) ->
      let* v1 = eval_env env e1 in
      let* v2 = eval_env env e2 in
      (match v1 with
        | VClosure (x, body, clo_env) ->
            eval_env (M.add x v2 clo_env) body
        | VRecClosure (f, x, body, clo_env) as c ->
            eval_env (clo_env |> M.add x v2 |> M.add f c) body
        | _ -> failwith "not a function")
  (* rzuca wyjatek poprzez None ktore zapobiegnie wykonywaniu sie dalszych obliczen *)
  | Throw -> None
  (* try e1 with e2 działa jak konstrukcja catch *)
  | Try (e1, e2) ->
      (match eval_env env e1 with
        | Some v1 -> Some v1         (* jeśli się udało – zwroc wynik *)
        | None -> eval_env env e2)   (* jeśli był throw – ewaluujemy e2 *)
  | _ -> failwith("todo")

let eval e = eval_env M.empty e

let interp (s : string) : value =
  match eval (parse s) with
  | Some v -> v
  | None -> failwith "unhandled exception"