
(* Zaproponuj składnie abstrakcyjna w postaci definicji typu w OCamlu 
   dla nastepujacych konkretnych notacji *)

(* for i := n to m do ... end (* pętla w Pascalu *) *)
(* calka oznaczona od k do n z f(x)dx *)

type bop =
  | Add | Sub | Mult | Div
  | And | Or
  | Eq | Leq
 
type ident = string
 
type expr = 
  | Int   of int
  | Binop of bop * expr * expr
  | Bool  of bool
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident
  (*            i  *  n  *  m  * body       *)
  | For   of ident * expr * expr * expr
  (*             k  *  n  * f(x) * dx       *)
  | Integral of expr * expr * expr * ident