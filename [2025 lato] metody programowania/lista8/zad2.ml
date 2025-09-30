
(*
Dwa wyrazenia nazywamy  α-równowaznymi, gdy róznia sie tylko nazwami
zmiennych zwiazanych i maja taka sama strukture przykrywania zmiennych.

np:
let x = 2 in let y = 5 in x + y
let y = 2 in let z = 5 in y + z

let x = 2 in x + y
let z = 2 in z + y

Zaimplementuj funkcje która sprawdza czy dwa wyrazenia dla jezyka LET z wykładu sa α-równowazne.
*)

type bop = | Add | Sub | Mult | Div | And | Or | Eq | Leq
type ident = string
type expr = 
  | Int   of int
  | Bool  of bool
  | Binop of bop * expr * expr
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident

module M = Map.Make(String)
type env = string M.t

(*
env1: (zmienne z e1 -> zmienne z e2)
env2: (zmienne z e2 -> zmienne z e1)
*)
let rec alpha_equiv_hlp (e1 : expr) (e2 : expr) (env1 : env) (env2 : env) : bool = 
  match e1, e2 with
  | Int a, Int b -> a = b
  | Bool a, Bool b -> a = b

  | Binop (bop1, e1l, e1r), Binop (bop2, e2l, e2r) ->
      bop1 = bop2 &&
      alpha_equiv_hlp e1l e2l env1 env2 &&
      alpha_equiv_hlp e1r e2r env1 env2

  | If (c1, t1, e1), If (c2, t2, e2) ->
      alpha_equiv_hlp c1 c2 env1 env2 &&
      alpha_equiv_hlp t1 t2 env1 env2 &&
      alpha_equiv_hlp e1 e2 env1 env2

  | Let (x1, e1l, e1r), Let (x2, e2l, e2r) ->
      alpha_equiv_hlp e1l e2l env1 env2 &&
      alpha_equiv_hlp e1r e2r (M.add x1 x2 env1) (M.add x2 x1 env2)

  | Var x, Var y ->
      (match M.find_opt x env1, M.find_opt y env2 with
      | Some y', Some x' -> x = x' && y = y'
      | None, None -> x = y
      | _, _ -> false
      )

  | _, _ -> false

let alpha_equiv (e1 : expr) (e2 : expr) : bool =
  alpha_equiv_hlp e1 e2 M.empty M.empty