
(* Napisz funkcje, która sprawdza, czy wyrazenie jezyka LET z wykładu jest ˙
zamkniete, czyli nie ma w nim zmiennych wolnych *)
type bop =
  | Add | Sub | Mult | Div
  | And | Or
  | Eq | Leq

type ident = string

type expr =
  | Int   of int
  | Bool  of bool
  | Binop of bop * expr * expr
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident

let is_closed ( e : expr ) : bool =
  let rec check e known = 
    match e with 
    | Int _ -> true
    | Bool _ -> true
    | Binop (_, e1, e2) -> check e1 known && check e2 known
    | If (p, t, e) -> check p known && check t known && check e known
    | Let (x, e1, e2) -> check e1 known && check e2 (x :: known)
    | Var x -> List.mem x known
    in check e [];;

(* testy *)
open Let;;
open Ast;;
open Parser;;
let parse (s : string) : expr =
    Parser.main Lexer.read (Lexing.from_string s);;

let parsed_expr = parse "let x = 5 in x + 2" in is_closed parsed_expr;;
let parsed_expr = parse "let x = 5 in x + y + 2" in is_closed parsed_expr;;
let parsed_expr = parse "let x = 2 in if x = 5 then 2 else 1" in is_closed parsed_expr;;
let parsed_expr = parse "let x = 2 in if y = 5 then 2 else 1" in is_closed parsed_expr;;