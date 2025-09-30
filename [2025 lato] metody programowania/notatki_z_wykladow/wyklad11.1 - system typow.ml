(*------------------------------- TYPY -------------------------------*)
(* - typ określa jaka wynik produkuje wyrazenie expr *)
(* - przechowuje tylko informacje o ewentualnych podtypach *)
type typ =
  | TUnit
  | TInt
  | TBool
  (* TPair(typ_pierwszego_elementu, typ_drugiego_elementu *)
  | TPair  of typ * typ
  (* TArrow(typ_argumentu, typ_wyniku) *)
  | TArrow of typ * typ          

(* pozwala na dokladniejsze zapisywanie komunikatow bledow *)
(* kazde expr to expr_data + pozycja w kodzie *)
type 'a node =
  { data : 'a
  ; pos  : Lexing.position * Lexing.position
  }

(* AST *)
type bop = | Add | Sub | Mult | Div | And 
| Or | Eq | Neq | Leq | Lt | Geq | Gt
type ident = string
type expr = expr_data node
and expr_data =
  | Unit
  | Int    of int
  | Bool   of bool
  | Var    of ident
  | Binop  of bop * expr * expr
  | If     of expr * expr * expr
  | Let    of ident * expr * expr
  | Pair   of expr * expr
  (* App(funkcja, argument) *)
  | App    of expr * expr                   
  | Fst    of expr
  | Snd    of expr
  (* Fun(nazwa_funkcji, typ_argumentu, ciało_funkcji) *)
  | Fun    of ident * typ * expr   
  (* Funrec(nazwa_funkcji, nazwa_argmentu, typ_argumentu, typ_wyniku, ciało_funkcji) *)
  | Funrec of ident * ident * typ * typ * expr;;

(*------------------------------- WERYFIKOWANIE TYPOW -------------------------------*)

exception Type_error of (Lexing.position * Lexing.position) * string

(* moduł na środowisko zeby wyizolowac funkcjie pomocnicze *)
module Env = struct
  (* mapa z stringami jako kluczami i typem jako wartoscia *)
  module StrMap = Map.Make(String)
  type t = typ StrMap.t

  let initial = StrMap.empty

  let add_var env x tp =
    StrMap.add x tp env

  let lookup_var env x =
    StrMap.find_opt x env
end

(* dla drzewa AST wyznacza typ jego wyniku *)
let rec infer_type env (e : expr) : typ =
  match e.data with
  | Unit   -> TUnit
  | Int  _ -> TInt
  | Bool _ -> TBool
  (* typ zmiennej powinien byc zapisany w srodowisku pod nazwa zmiennej *)
  | Var  x ->
    begin match Env.lookup_var env x with
    | Some tp -> tp
    | None    ->
      raise (Type_error(e.pos,
        Printf.sprintf "Unbound variable %s" x))
    end
  (* weryfikujemy czy operujemy na intach *)
  | Binop((Add | Sub | Mult | Div), e1, e2) ->
    check_type env e1 TInt;
    check_type env e2 TInt;
    TInt                                                   (* zwracamy typ wyniku operacji *)
  (* weryfikujemy czy operujemy na boolach *)
  | Binop((And | Or), e1, e2) ->
    check_type env e1 TBool;
    check_type env e2 TBool;
    TBool
  (* weryfikujemy czy porownania sa na intach *)
  | Binop((Leq | Lt | Geq | Gt), e1, e2) ->
    check_type env e1 TInt;
    check_type env e2 TInt;
    TBool
  (* weryfikujemy czy porownania sa na tych samych typach *)
  | Binop((Eq | Neq), e1, e2) ->
    let tp = infer_type env e1 in
    check_type env e2 tp;
    TBool
  (* weryfikujemy czy b to bool a e1 i e2 maja ten sam typ *)
  | If(b, e1, e2) ->
    check_type env b TBool;
    let tp = infer_type env e1 in
    check_type env e2 tp;
    tp
  (* dodajemy do srodowiska env2 typ e1 *)
  | Let(x, e1, e2) ->
    let tp1 = infer_type env e1 in
    let tp2 = infer_type (Env.add_var env x tp1) e2 in
    tp2
  (* szukamy typu dla kazdego elementu pary osobno *)
  | Pair(e1, e2) ->
    TPair(infer_type env e1, infer_type env e2)
  (* e1 musi byc typu TArrow (wynik infer_type dla Fun() i Funrec()) *)
  (* a typ aplikowanego argumentu (e2) musi sie zgadzac z typem argumentu (tp2) funkcji e1 *)
  | App(e1, e2) ->                                               (* App(funkcja, argument) *)
    begin match infer_type env e1 with
    | TArrow(tp2, tp1) ->                             (* TArrow(typ_argumentu, typ_wyniku) *)
      check_type env e2 tp2;
      tp1
    | _ -> failwith "Type error"
    end
  (* typ e musi byc TPair, zwracamy tp1 *)
  | Fst e ->
    begin match infer_type env e with
    | TPair(tp1, _) -> tp1
    | _ -> failwith "Type error"
    end
  (* typ e musi byc TPair, zwracamy tp2 *)
  | Snd e ->
    begin match infer_type env e with
    | TPair(_, tp2) -> tp2
    | _ -> failwith "Type error"
    end
  (* dodajemy (x -> tp1) czyli argument i jego typ do env *)
  (* wnioskujemy typ ciała funkcji i zwracamy TArrow *)
  | Fun(x, tp1, e) ->                   (* Fun(nazwa_funkcji, typ_argumentu, ciało_funkcji) *)
    let tp2 = infer_type (Env.add_var env x tp1) e in
    TArrow(tp1, tp2)
  (* dodajemy (x -> tp1) oraz (f -> TArrow(typ_arg, typ_wyn)) do env *)
  (* sprawdzamy czy ciało tez ma typ wynikowy tp2 *)
  | Funrec(f, x, tp1, tp2, e) ->    (* Funrec(nazw_f, nazw_arg, typ_arg, typ_wyn, ciało_f) *)
    let env = Env.add_var env x tp1 in
    let env = Env.add_var env f (TArrow(tp1, tp2)) in
    check_type env e tp2;
    TArrow(tp1, tp2)

and check_type env e tp =
  let tp' = infer_type env e in
  if tp = tp' then ()
  else failwith "Type error";;

let check_program e = let _ = infer_type Env.initial e in e;;

(*------------------------------- PARSER -------------------------------*)

main:
    | e = mexpr; EOF { e }
    ;

(* wyrazenia okreslajace typ *)
type_expr:
    | tp = type_simpl { tp }
    | tp1 = type_expr; ARR; tp2 = type_expr
      { TArrow(tp1, tp2) }
    | tp1 = type_expr; TIMES; tp2 = type_expr
      { TPair(tp1, tp2) }
    ;
type_simpl:
    | KW_INT  { TInt  }
    | KW_BOOL { TBool }
    | KW_UNIT { TUnit }
    | LPAREN; tp = type_expr; RPAREN { tp }
;

(* musimy recznie okreslic typy tylko w funkcjach *)
(* bo w innych przypadkach mozemy sami wywnioskowac w infer_type *)
mexpr:
    | IF; e1 = mexpr; THEN; e2 = mexpr; ELSE; e3 = mexpr
        { node $loc (If(e1, e2, e3)) }
    | LET; x = IDENT; EQ; e1 = mexpr; IN; e2 = mexpr
        { node $loc (Let(x, e1, e2)) }
    (* fun (x : tp) -> e *)
    | FUN;
      LPAREN; x = IDENT; COLON; tp = type_expr; RPAREN;
      ARR; e = mexpr
        { node $loc (Fun(x, tp, e)) }
    (* funrec f (x : tp1) : tp2 -> e *)
    | FUNREC; f = IDENT;
      LPAREN; x = IDENT; COLON; tp1 = type_expr; RPAREN;
      COLON; tp2 = type_simpl; ARR; e = mexpr
        { node $loc (Funrec(f, x, tp1, tp2, e)) }
    | e = expr { e }
    ;

expr:
    | e1 = expr; PLUS; e2 = expr
      { node $loc (Binop(Add, e1, e2)) }
  (* ... *)
    | e1 = expr; AND; e2 = expr
      { node $loc (Binop(And, e1, e2)) }

app_expr:
    | FST; e = base_expr { node $loc (Fst e) }
    | SND; e = base_expr { node $loc (Snd e) }
    | e1 = app_expr; e2 = base_expr { node $loc (App (e1, e2)) }
    | e = base_expr { e }
    ;

base_expr:
    | x = IDENT { node $loc (Var x) }
    | i = INT { node $loc (Int i) }
    | b = BOOL { node $loc (Bool b) }
    | UNIT { node $loc Unit }
    | LPAREN; e1 = mexpr; COMMA; e2 = mexpr; RPAREN {
      node $loc (Pair (e1,e2)) }
    | LPAREN; e = mexpr; RPAREN
      { node $loc (e.data) }
    ;
