
(* AST.ML 
    - definicje typow w AST *)

(* PARSER.MLY 
    - otworzenie AST zeby dostac typy
    - deklaracje tokenow 
    - priorytety operatorow 
    - definiuje produkcje z tokenow lub innych produkcji *)

(* LEXTER.MLL
    - otworzenie parsera zeby dostac tokeny
    - wyrazenia regularne definiujace syntaks tokenow
    - zasady produktowania tokenow *)

(*------------------------------- KONSTRUKTORY WPROWADZAJACE/ELIMINUJACE -------------------------------*)
(* WPROWADZAJACY - tworzy wartośc danego typu *)
(* ELIMINUJACY - uzywa/rozkłada wartosc danego typu zeby uzyskac informacje ze środka *)
let b = true;;                      (* wprowadzające *)
let x = if b then 1 else 0;;        (* eliminujące *)
(* 
let e = Binop (Add, Int 2, Int 3)   (* wprowadzające *)
let wynik =           
  match e with                      (* eliminujące *)
  | Binop (Add, Int a, Int b) -> a + b
  | _ -> 0 
*)

(*------------------------------- TYPY -------------------------------*)

type bop = Add | Sub | Mult | Div                   (* AST *)
type ident = string
type expr = 
  | Int   of int
  | Binop of bop * expr * expr
  | Bool  of bool
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident
  | Pair  of expr * expr
  | Fst   of expr
  | Snd   of expr
  | Match of expr * ident * ident * expr
  | Unit

type value =                                        (* wynik ewualuacji *)
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value                 

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | _ -> failwith("todo")

(*------------------------------- MODEL PODSTAWIENIOWY -------------------------------*)
(* do obslugiwania konstrukcji let *)
(* polega na substytucji zmiennej x poprzez s jak w (let x = 5 in x + 2), s = (Int 5) *)
(* let x = 5 in (x + 2) -----> Let("x", Int 5, Binop(+, "x", Int 2)) *)
let rec subst (x : ident) (s : expr) (e : expr) : expr =
  match e with
  | Binop (op, e1, e2) -> Binop (op, subst x s e1, subst x s e2)
  | If (b, t, e) -> If (subst x s b, subst x s t, subst x s e)
  (* właściwa substytucja na poziomie zmiennej *)
  | Var y -> if x = y then s else e       
  (* jezeli napotykamy nowe wyrazenie let() to robimy substytuje w e1 
     a w e3 tylko jezeli x != y bo inaczej w e2 wystepuja lokalne zwiazanie
     y, ktorego nie chcielibysmy nadpisac naszym x mimo ze nazywaja sie tak samo *)
  | Let (y, e1, e2) -> Let (y, subst x s e1, if x = y then e2 else subst x s e2)
  | Pair (e1, e2) -> Pair (subst x s e1, subst x s e2)
  | Fst e -> Fst (subst x s e)
  | Snd e -> Snd (subst x s e)
  | Match (e1, z, y, e2) -> Match (subst x s e1, z, y, (if x = z || x = y then e2 else subst x s e2))
  | _ -> e

(*------------------------------- REIFIKACJA -------------------------------*)
(* konwersja wartości po ewaluacji (value) z powrotem do wyrażenia expr (AST) *)
(* potrzebne do ewaluacji let w modelu podstawieniowym, 
   ponieważ subst działa na expr, nie na value *)
let rec reify (v : value) : expr =
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b
  | VPair (v1, v2) -> Pair (reify v1, reify v2)
  | VUnit -> Unit

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
  | Pair (e1, e2) -> VPair (eval e1, eval e2)
  | Unit -> VUnit
  | Fst e ->                    (* ewaluacja e musi dac nam pare! *)
      (match eval e with
        | VPair (v1, _) -> v1
        | _ -> failwith "Type error")
  | Snd e ->
      (match eval e with
        | VPair (_, v2) -> v2
        | _ -> failwith "Type error")
  | Match (e1, x, y, e2) ->
      (match eval e1 with
        | VPair (v1, v2) ->
            e2
            |> subst x (reify v1)
            |> subst y (reify v2)
            |> eval
        | _ -> failwith "Type error")
  (* blad bo ta zmienna powinna byc juz podstawiona przez wyrazenia let *)
  | Var x -> failwith ("unknown var " ^ x) 