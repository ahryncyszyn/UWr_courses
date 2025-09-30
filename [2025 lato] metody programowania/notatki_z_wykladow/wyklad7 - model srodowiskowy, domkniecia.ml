
(*------------------------------- MODEL ŚRODOWISKOWY  -------------------------------*)
(* 
MODEL ŚRODOWISKOWY - zamiast podmieniać zmienne na wartości, interpreter 
przechowuje środowisko (mape env), czyli mapowanie nazw zmiennych na wartości
- przy napotykaniu zmiennej, szukamy jej w srodowisku
- bardziej naturalna obsluga domkniec i rekurencji

MODEL PODSTAWIENIOWY - zamiast trzymać środowisko zmiennych, interpreter
symuluje działanie programu poprzez "wklejanie" wartości bezpośrednio w miejsce zmiennych
- problemy z kolizjami nazw
*)

(*------------------------------- TYPY -------------------------------*)

type bop = | Add | Sub | Mult | Div | And                      (* AST *)
type ident = string
type expr = 
  | Int    of int
  | Binop  of bop * expr * expr
  | Bool   of bool
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

(* Map.Make to funktor ktory przyjmuje (Ord : OrderedType) *)
(* tworzy modul z type key = Ord.t *)
(* tutaj M to mapa (string -> value) gdzie kazdy string to zmienna *)
module M = Map.Make(String) 

(* and oznacza wzjemnie rekurencyjne typy *)     
(* typ env to mapa z kluczami typu M.t (string) i danymi typu value *)
type env = value M.t
and value =                       
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  (* funkcja anonimowa (fun x -> e) razem ze swoim env *)
  | VClosure of ident * expr * env       
  (* funkcja rekurencyjna (funrec f x -> e) razem ze swoim env *)         
  | VRecClosure of ident * ident * expr * env;;

(*------------------------------- PARSER -------------------------------*)

main:
    | e = mexpr; EOF { e }
    ;

mexpr:
    | IF; e1 = mexpr; THEN; e2 = mexpr; ELSE; e3 = mexpr { If(e1, e2, e3) }
    | LET; x = IDENT; EQ; e1 = mexpr; IN; e2 = mexpr { Let(x, e1, e2) }
    (* ... *)
    (* funkcja anonimowa (fun x -> e) *)
    | FUN; x = IDENT; ARR; e = mexpr { Fun(x, e) }
    (* funkcja rekurencyjna (funrec f x -> e) *)
    | FUNREC; f = IDENT; x = IDENT; ARR; e = mexpr { Funrec(f, x, e) }
    | e = expr { e }
    ;

expr:
    (* ... *)
    | e = app_expr { e }

app_expr:
    | ISPAIR; e1 = base_expr { IsPair e1 }
    | FST; e = base_expr { Fst e }
    | SND; e = base_expr { Snd e }
    (* ... *)
    (* wywolanie funkcji e1 razem z jej argumentem e2, np (fun x -> x + 1) 5 *)
    (* bo app_expr moze byc base_expr ktore moze byc mexpr w nawiasach *)
    | e1 = app_expr; e2 = base_expr { App (e1, e2) }
    | e = base_expr { e }
    ; 

base_expr:
    | x = IDENT { Var x }
    | i = INT { Int i }
    | b = BOOL { Bool b }
    | LPAREN; e1 = mexpr; COMMA; e2 = mexpr; RPAREN { Pair (e1,e2) }
    | LPAREN; e = mexpr; RPAREN { e }
    ;

(*------------------------------- DOMKNIECIE -------------------------------*)
(* funkcja + srodowisko w ktorym została zdefiniowana *)
(* APLIKACJA FUNKCJI  
- FUN 
  - dodajemy (argument -> wartosc) do srodowiska 
  - ewaluujemy cialo funkcji z nowym srodowiskiem
- FUNREC: 
  - dodajemy (argument -> wartosc) do srodowiska 
  - dodajemy (nazwa_funkcji -> ciało funkcji) do srodowiska
  - ewaluujemy cialo funkcji z nowym srodowiskiem
*)

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | _ -> failwith("todo")

let rec eval_env (env : env) (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval_env env e1) (eval_env env e2)
  (* mozemy ewaluowac zmienne - wystarczy poszukac wartosci w env *)
  | Var x ->
     (match M.find_opt x env with   
       | Some v -> v
       | None -> failwith "unknown var")
  (* związanie zmiennej polega na dodaniu jej do env *)
  | Let (x, e1, e2) ->
      eval_env (M.add x (eval_env env e1) env) e2
  (* ... *)
  (* tworzenie domkniecia, czyli funkcja + env *)
  | Fun (x, e) -> VClosure (x, e, env)              
  (* funkcja rekurencyjna musi znac samą siebie *)
  | Funrec (f, x, e) -> VRecClosure (f, x, e, env)  
  (* e1 powinno byc funkcja (domknieciem), a e2 wartoscia argumentu *)
  (* aplikacja funkcji polega na dodaniu argumentu i jego
    wartosci do srodowiska a potem ewaluowaniu ciala funkcji *)
  | App (e1, e2) ->
      let v1 = eval_env env e1 in
      let v2 = eval_env env e2 in
      (match v1 with
        | VClosure (x, body, clo_env) ->
          (* ewaluujemy cialo funkcji z wartoscia x dodana do env *)
            eval_env (M.add x v2 clo_env) body
        | VRecClosure (f, x, body, clo_env) as c ->
          (* "as c" zapisuje cale domkniecie i dodaje je do env pod kluczem f *)
            eval_env (clo_env |> M.add x v2 |> M.add f c) body
        | _ -> failwith "not a function")


(*------------------------------- SHOW VALUE -------------------------------*)
(* funkcja pomocnicza do debugowania *)
let rec show_value v =
  match v with
  | VInt n -> string_of_int n
  | VBool v -> string_of_bool v
  | VUnit -> "()"
  | VPair (v1,v2) -> "(" ^ show_value v1 ^ ", " ^ show_value v2 ^ ")"
  | VClosure _ | VRecClosure _ -> "<fun>"