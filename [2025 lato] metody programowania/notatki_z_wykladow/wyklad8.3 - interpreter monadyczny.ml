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
  | Match  of expr * ident * ident * expr
  | IsPair of expr
  | Fun    of ident * expr
  | Funrec of ident * ident * expr
  | App    of expr * expr
  | Ref    of expr
  | Deref  of expr

(*------------------------------- INTERPRETER MONADYCZNY -------------------------------*)
(* MONADA - sposób na sekwencjonowanie obliczeń z efektami ubocznymi *)
(* - tu monada opakowuje funkcję typu 'a comp = heap -> ('a * heap) *)
(* - typ 'a comp reprezentuje obliczenie, które zwraca wynik typu 'a i może zmienić stertę (heap) *)
(* - umozliwia jawne zarzadzanie sterta bez koniecznosci przekazywania jej recznie! *)
(* - ewaluacja tworzy zagniezdzone funkcje czekajace na zaaplikowanie sterty (na koncu w run) *)

(* moduły env i heap *)
module M = Map.Make(String)
module Loc = Int
module H = Map.Make(Loc)

(* generator nowych adresow *)
let fresh h = H.cardinal h
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
(* reprezentuje obliczenie, które bierze stertę, a zwraca wynik typu 'a i stertę *)
type 'a comp = heap -> 'a * heap

(* zawija wyrazenie w 'a comp bez zmiany stanu (heap) *)
let return (v : 'a) : 'a comp =
  fun h -> (v, h)

(* łączy dwa obliczenia: wykonuje c, bierze wynik v, przekazuje do f *)
(* uzywane jako "let* x = e1 in e2", co jest tozsame z "bind e1 (fun x -> e2)"!!*)
let bind (c : 'a comp) (f : 'a -> 'b comp) : 'b comp =
  fun h -> let (v, h) = c h     (* aplikacja h do c zwraca ('a, heap) *)
in f v h                        (* aplikacja (v : 'a) do f zwraca 'b comp *)
                                (* a aplikacja h do 'b comp zwraca ('b, heap) *)

(* cukier syntaktyczny na bind *)
let (let*) = bind

(* tworzy nowa referencje (adres na stercie) *)
let refc (v : value) : Loc.t comp =
  fun h ->
    let r = fresh h in
    (r, H.add r v h)      (* zwraca zmodyfikowana sterte *)
  
let derefc (l : Loc.t) : value comp =
  fun h -> (H.find l h, h)

let assgn (l : Loc.t) (v : value) : unit comp =
  fun h -> ((), H.add l v h)  (* modyfikuje wartosc pod adresem l na v *)

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

let eval_op (op : bop) : value -> value -> value comp =
  match op with
  | Add  -> int_op ( + )
  | Sub  -> int_op ( - )
  | Eq   -> (fun v1 v2 h -> (VBool (v1 = v2), h))
  | Neq  -> (fun v1 v2 h -> (VBool (v1 <> v2), h))
  | Assgn -> (fun v1 v2 ->
      match v1 with
      | VRef r ->
        let* _ = assgn r v2 in
        return VUnit
      | _ -> failwith "type error")
  | _ -> failwith("todo")

(* buduje zagniezdzone funkcje (heap -> (value * heap) ktore czekaja 
   na aplikacje sterty na koncu a potem automatycznie ja przekazuja *)
let rec eval_env (env : env) (e : expr) : value comp =
  match e with
  | Int i -> return (VInt i)
  | Bool b -> return (VBool b)
  | Binop (op, e1, e2) ->
      bind (eval_env env e1) (fun v1 -> (* let* v1 = eval_env env e1 in *)
      bind (eval_env env e2) (fun v2 ->
      eval_op op v1 v2))
  | If (b, t, e) ->
      let* v = eval_env env b in
      (match v with
      | VBool true -> eval_env env t
      | VBool false -> eval_env env e
      | _ -> failwith "type error")
  | Var x ->
      let v =
        match M.find_opt x env with
        | Some v -> v
        | None -> failwith "unknown var"
      in
      return v
  | Let (x, e1, e2) ->
      let* v1 = eval_env env e1 in
      eval_env (env |> M.add x v1) e2
  | Fst e ->
      let* v = eval_env env e in
      (match v with
        | VPair (v1, _) -> return v1
        | _ -> failwith "Type error")
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
  (* 
  po odcukrzeniu let* kod tozsamy z:
  bind (eval_env env e) (fun v ->
  bind (refc v) (fun r ->
    return (VRef r)))
  *)
  | Ref e ->
      let* v = eval_env env e in
      let* r = refc v in
      return (VRef r)
  | Deref e ->
      let* v = eval_env env e in
      (match v with
        | VRef r -> derefc r
        | _ -> failwith "not a reference")
  | _ -> failwith("todo")

(* aplikujac H.empty a potem fst do value comp izolujemy wynik!! *)
let run c = fst (c H.empty)

(* eval_env zwraca value comp *)
let eval e = run (eval_env M.empty e)

